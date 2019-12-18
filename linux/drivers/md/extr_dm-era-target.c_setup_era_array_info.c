#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct era_metadata {int /*<<< orphan*/  tm; int /*<<< orphan*/  era_array_info; } ;
struct dm_btree_value_type {int size; int /*<<< orphan*/ * equal; int /*<<< orphan*/ * dec; int /*<<< orphan*/ * inc; int /*<<< orphan*/ * context; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  dm_array_info_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dm_btree_value_type*) ; 

__attribute__((used)) static void setup_era_array_info(struct era_metadata *md)

{
	struct dm_btree_value_type vt;
	vt.context = NULL;
	vt.size = sizeof(__le32);
	vt.inc = NULL;
	vt.dec = NULL;
	vt.equal = NULL;

	dm_array_info_init(&md->era_array_info, md->tm, &vt);
}