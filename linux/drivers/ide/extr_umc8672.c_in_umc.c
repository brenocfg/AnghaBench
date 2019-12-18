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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  inb_p (int) ; 
 int /*<<< orphan*/  outb_p (char,int) ; 

__attribute__((used)) static inline u8 in_umc(char port)
{
	outb_p(port, 0x108);
	return inb_p(0x109);
}