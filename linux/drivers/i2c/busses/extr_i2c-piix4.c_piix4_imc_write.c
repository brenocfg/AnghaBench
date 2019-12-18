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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERNCZ_IMC_DATA ; 
 int /*<<< orphan*/  KERNCZ_IMC_IDX ; 
 int /*<<< orphan*/  outb_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void piix4_imc_write(uint8_t idx, uint8_t value)
{
	outb_p(idx, KERNCZ_IMC_IDX);
	outb_p(value, KERNCZ_IMC_DATA);
}