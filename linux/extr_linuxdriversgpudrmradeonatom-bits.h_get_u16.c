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
typedef  int uint16_t ;

/* Variables and functions */
 int get_u8 (void*,int) ; 

__attribute__((used)) static inline uint16_t get_u16(void *bios, int ptr)
{
    return get_u8(bios ,ptr)|(((uint16_t)get_u8(bios, ptr+1))<<8);
}