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
struct bfa_cee_attr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_DMA_ALIGN_SZ ; 
 int /*<<< orphan*/  roundup (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32
bfa_cee_attr_meminfo(void)
{
	return roundup(sizeof(struct bfa_cee_attr), BFA_DMA_ALIGN_SZ);
}