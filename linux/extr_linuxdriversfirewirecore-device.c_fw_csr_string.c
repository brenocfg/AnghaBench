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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/ * search_leaf (int /*<<< orphan*/  const*,int) ; 
 int textual_leaf_to_string (int /*<<< orphan*/  const*,char*,size_t) ; 

int fw_csr_string(const u32 *directory, int key, char *buf, size_t size)
{
	const u32 *leaf = search_leaf(directory, key);
	if (!leaf)
		return -ENOENT;

	return textual_leaf_to_string(leaf, buf, size);
}