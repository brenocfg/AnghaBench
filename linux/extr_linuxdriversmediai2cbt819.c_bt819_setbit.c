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
typedef  size_t u8 ;
struct bt819 {int* reg; } ;

/* Variables and functions */
 int bt819_write (struct bt819*,size_t,int) ; 

__attribute__((used)) static inline int bt819_setbit(struct bt819 *decoder, u8 reg, u8 bit, u8 value)
{
	return bt819_write(decoder, reg,
		(decoder->reg[reg] & ~(1 << bit)) | (value ? (1 << bit) : 0));
}