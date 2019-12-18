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
struct tty_struct {int dummy; } ;

/* Variables and functions */
 int __sclp_vt220_write (unsigned char const*,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
sclp_vt220_write(struct tty_struct *tty, const unsigned char *buf, int count)
{
	return __sclp_vt220_write(buf, count, 1, 0, 1);
}