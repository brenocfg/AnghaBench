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
struct dm_btree_info {int /*<<< orphan*/  tm; } ;
typedef  int /*<<< orphan*/  root_le ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  dm_tm_inc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int) ; 

__attribute__((used)) static void subtree_inc(void *context, const void *value)
{
	struct dm_btree_info *info = context;
	__le64 root_le;
	uint64_t root;

	memcpy(&root_le, value, sizeof(root_le));
	root = le64_to_cpu(root_le);
	dm_tm_inc(info->tm, root);
}