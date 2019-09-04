#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct serverworks_page_map {int dummy; } ;
struct TYPE_2__ {int num_tables; struct serverworks_page_map** gatt_pages; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct serverworks_page_map** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 struct serverworks_page_map* kzalloc (int,int /*<<< orphan*/ ) ; 
 int serverworks_create_page_map (struct serverworks_page_map*) ; 
 int /*<<< orphan*/  serverworks_free_gatt_pages () ; 
 TYPE_1__ serverworks_private ; 

__attribute__((used)) static int serverworks_create_gatt_pages(int nr_tables)
{
	struct serverworks_page_map **tables;
	struct serverworks_page_map *entry;
	int retval = 0;
	int i;

	tables = kcalloc(nr_tables + 1, sizeof(struct serverworks_page_map *),
			 GFP_KERNEL);
	if (tables == NULL)
		return -ENOMEM;

	for (i = 0; i < nr_tables; i++) {
		entry = kzalloc(sizeof(struct serverworks_page_map), GFP_KERNEL);
		if (entry == NULL) {
			retval = -ENOMEM;
			break;
		}
		tables[i] = entry;
		retval = serverworks_create_page_map(entry);
		if (retval != 0) break;
	}
	serverworks_private.num_tables = nr_tables;
	serverworks_private.gatt_pages = tables;

	if (retval != 0) serverworks_free_gatt_pages();

	return retval;
}