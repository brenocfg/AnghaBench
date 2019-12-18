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
typedef  int /*<<< orphan*/  uint64_t ;
struct mapped_device {int dummy; } ;
struct hash_cell {int dummy; } ;

/* Variables and functions */
 struct mapped_device* dm_get_md (int /*<<< orphan*/ ) ; 
 struct hash_cell* dm_get_mdptr (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_put (struct mapped_device*) ; 
 int /*<<< orphan*/  huge_decode_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct hash_cell *__get_dev_cell(uint64_t dev)
{
	struct mapped_device *md;
	struct hash_cell *hc;

	md = dm_get_md(huge_decode_dev(dev));
	if (!md)
		return NULL;

	hc = dm_get_mdptr(md);
	if (!hc) {
		dm_put(md);
		return NULL;
	}

	return hc;
}