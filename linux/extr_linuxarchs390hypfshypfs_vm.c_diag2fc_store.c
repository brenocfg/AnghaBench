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
struct diag2fc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ diag2fc (int,char*,void*) ; 
 int /*<<< orphan*/  vfree (void*) ; 
 void* vmalloc (int) ; 

__attribute__((used)) static void *diag2fc_store(char *query, unsigned int *count, int offset)
{
	void *data;
	int size;

	do {
		size = diag2fc(0, query, NULL);
		if (size < 0)
			return ERR_PTR(-EACCES);
		data = vmalloc(size + offset);
		if (!data)
			return ERR_PTR(-ENOMEM);
		if (diag2fc(size, query, data + offset) == 0)
			break;
		vfree(data);
	} while (1);
	*count = (size / sizeof(struct diag2fc_data));

	return data;
}