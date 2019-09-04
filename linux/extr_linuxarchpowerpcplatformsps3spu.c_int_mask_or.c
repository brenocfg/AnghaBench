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
typedef  int u64 ;
struct spu {int dummy; } ;

/* Variables and functions */
 int spu_int_mask_get (struct spu*,int) ; 
 int /*<<< orphan*/  spu_int_mask_set (struct spu*,int,int) ; 

__attribute__((used)) static void int_mask_or(struct spu *spu, int class, u64 mask)
{
	u64 old_mask;

	old_mask = spu_int_mask_get(spu, class);
	spu_int_mask_set(spu, class, old_mask | mask);
}