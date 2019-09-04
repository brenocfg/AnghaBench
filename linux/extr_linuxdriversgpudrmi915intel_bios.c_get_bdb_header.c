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
struct vbt_header {int bdb_offset; } ;
typedef  void bdb_header ;

/* Variables and functions */

__attribute__((used)) static const struct bdb_header *get_bdb_header(const struct vbt_header *vbt)
{
	const void *_vbt = vbt;

	return _vbt + vbt->bdb_offset;
}