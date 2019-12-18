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
typedef  int /*<<< orphan*/  u64 ;
struct nd_namespace_blk {int dummy; } ;
struct bio_integrity_payload {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int nd_blk_rw_integrity(struct nd_namespace_blk *nsblk,
		struct bio_integrity_payload *bip, u64 lba, int rw)
{
	return 0;
}