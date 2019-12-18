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
typedef  unsigned char u8 ;
typedef  size_t u32 ;
struct arc4context {int dummy; } ;

/* Variables and functions */
 scalar_t__ arcfour_byte (struct arc4context*) ; 

__attribute__((used)) static void arcfour_encrypt(struct arc4context	*parc4ctx,
		     u8 *dest, u8 *src, u32 len)
{
	u32 i;

	for (i = 0; i < len; i++)
		dest[i] = src[i] ^ (unsigned char)arcfour_byte(parc4ctx);
}