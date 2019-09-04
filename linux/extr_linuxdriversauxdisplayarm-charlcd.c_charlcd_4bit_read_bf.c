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
struct charlcd {scalar_t__ irq; scalar_t__ virtbase; int /*<<< orphan*/  complete; } ;

/* Variables and functions */
 scalar_t__ CHAR_COM ; 
 scalar_t__ CHAR_MASK ; 
 scalar_t__ CHAR_RAW ; 
 int CHAR_RAW_CLEAR ; 
 int HD_BUSY_FLAG ; 
 int charlcd_4bit_read_char (struct charlcd*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static bool charlcd_4bit_read_bf(struct charlcd *lcd)
{
	if (lcd->irq >= 0) {
		/*
		 * If we'll use IRQs to wait for the busyflag, clear any
		 * pending flag and enable IRQ
		 */
		writel(CHAR_RAW_CLEAR, lcd->virtbase + CHAR_RAW);
		init_completion(&lcd->complete);
		writel(0x01, lcd->virtbase + CHAR_MASK);
	}
	readl(lcd->virtbase + CHAR_COM);
	return charlcd_4bit_read_char(lcd) & HD_BUSY_FLAG ? true : false;
}