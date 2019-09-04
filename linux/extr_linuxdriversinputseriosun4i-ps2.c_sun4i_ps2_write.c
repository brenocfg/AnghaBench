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
struct sun4i_ps2data {scalar_t__ reg_base; } ;
struct serio {struct sun4i_ps2data* port_data; } ;

/* Variables and functions */
 int PS2_FSTS_TXRDY ; 
 scalar_t__ PS2_REG_DATA ; 
 scalar_t__ PS2_REG_FSTS ; 
 int SERIO_TIMEOUT ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int readl (scalar_t__) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  writel (unsigned char,scalar_t__) ; 

__attribute__((used)) static int sun4i_ps2_write(struct serio *serio, unsigned char val)
{
	unsigned long expire = jiffies + msecs_to_jiffies(10000);
	struct sun4i_ps2data *drvdata = serio->port_data;

	do {
		if (readl(drvdata->reg_base + PS2_REG_FSTS) & PS2_FSTS_TXRDY) {
			writel(val, drvdata->reg_base + PS2_REG_DATA);
			return 0;
		}
	} while (time_before(jiffies, expire));

	return SERIO_TIMEOUT;
}