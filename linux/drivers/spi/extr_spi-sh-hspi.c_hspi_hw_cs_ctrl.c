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
struct hspi_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPSCR ; 
 int /*<<< orphan*/  hspi_bit_set (struct hspi_priv*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void hspi_hw_cs_ctrl(struct hspi_priv *hspi, int hi)
{
	hspi_bit_set(hspi, SPSCR, (1 << 6), (hi) << 6);
}