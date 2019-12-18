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
typedef  unsigned int u8 ;
struct dw_hdmi {int reg_shift; int /*<<< orphan*/  regm; } ;

/* Variables and functions */
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 

__attribute__((used)) static inline u8 hdmi_readb(struct dw_hdmi *hdmi, int offset)
{
	unsigned int val = 0;

	regmap_read(hdmi->regm, offset << hdmi->reg_shift, &val);

	return val;
}