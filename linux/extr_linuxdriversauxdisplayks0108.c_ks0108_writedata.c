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

/* Variables and functions */
 int /*<<< orphan*/  ks0108_parport ; 
 int /*<<< orphan*/  parport_write_data (int /*<<< orphan*/ ,unsigned char) ; 

void ks0108_writedata(unsigned char byte)
{
	parport_write_data(ks0108_parport, byte);
}