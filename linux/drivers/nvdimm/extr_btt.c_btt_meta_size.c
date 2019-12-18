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
typedef  scalar_t__ u32 ;
struct btt {scalar_t__ sector_size; scalar_t__ lbasize; } ;

/* Variables and functions */

__attribute__((used)) static u32 btt_meta_size(struct btt *btt)
{
	return btt->lbasize - btt->sector_size;
}