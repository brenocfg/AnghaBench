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
typedef  int /*<<< orphan*/  volatile __u8 ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 scalar_t__ FLASH_OFFSET ; 

__attribute__((used)) static __u8 read8 (__u32 offset)
{
   volatile __u8 *data = (__u8 *) (FLASH_OFFSET + offset);
#ifdef LART_DEBUG
   printk (KERN_DEBUG "%s(): 0x%.8x -> 0x%.2x\n", __func__, offset, *data);
#endif
   return (*data);
}