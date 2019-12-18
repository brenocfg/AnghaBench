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
struct pcf85363 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_RAMBYTE ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int pcf85x63_nvram_write(void *priv, unsigned int offset, void *val,
				size_t bytes)
{
	struct pcf85363 *pcf85363 = priv;
	unsigned char tmp_val;

	tmp_val = *((unsigned char *)val);
	return regmap_write(pcf85363->regmap, CTRL_RAMBYTE,
				(unsigned int)tmp_val);
}