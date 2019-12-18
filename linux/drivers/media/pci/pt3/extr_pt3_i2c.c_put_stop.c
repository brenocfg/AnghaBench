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
struct pt3_i2cbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_CLOCK_H ; 
 int /*<<< orphan*/  I_DATA_H ; 
 int /*<<< orphan*/  I_DATA_L ; 
 int /*<<< orphan*/  cmdbuf_add (struct pt3_i2cbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void put_stop(struct pt3_i2cbuf *cbuf)
{
	cmdbuf_add(cbuf, I_DATA_L);
	cmdbuf_add(cbuf, I_CLOCK_H);
	cmdbuf_add(cbuf, I_DATA_H);
}