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
struct v4l2_subdev {int dummy; } ;
struct m5mols_info {struct v4l2_subdev sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  MON_CFIXB ; 
 int /*<<< orphan*/  MON_CFIXR ; 
 int /*<<< orphan*/  MON_EFFECT ; 
 int /*<<< orphan*/  PARM_EFFECT ; 
 unsigned int REG_CFIXB_SEPIA ; 
 unsigned int REG_CFIXR_SEPIA ; 
 unsigned int REG_COLOR_EFFECT_OFF ; 
 unsigned int REG_COLOR_EFFECT_ON ; 
 unsigned int REG_EFFECT_EMBOSS ; 
 unsigned int REG_EFFECT_NEGA ; 
 unsigned int REG_EFFECT_OFF ; 
#define  V4L2_COLORFX_BW 131 
#define  V4L2_COLORFX_EMBOSS 130 
#define  V4L2_COLORFX_NEGATIVE 129 
#define  V4L2_COLORFX_SEPIA 128 
 int /*<<< orphan*/  m5mols_debug ; 
 int m5mols_write (struct v4l2_subdev*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,unsigned int,unsigned int,unsigned int,unsigned int,int) ; 

__attribute__((used)) static int m5mols_set_color_effect(struct m5mols_info *info, int val)
{
	unsigned int m_effect = REG_COLOR_EFFECT_OFF;
	unsigned int p_effect = REG_EFFECT_OFF;
	unsigned int cfix_r = 0, cfix_b = 0;
	struct v4l2_subdev *sd = &info->sd;
	int ret = 0;

	switch (val) {
	case V4L2_COLORFX_BW:
		m_effect = REG_COLOR_EFFECT_ON;
		break;
	case V4L2_COLORFX_NEGATIVE:
		p_effect = REG_EFFECT_NEGA;
		break;
	case V4L2_COLORFX_EMBOSS:
		p_effect = REG_EFFECT_EMBOSS;
		break;
	case V4L2_COLORFX_SEPIA:
		m_effect = REG_COLOR_EFFECT_ON;
		cfix_r = REG_CFIXR_SEPIA;
		cfix_b = REG_CFIXB_SEPIA;
		break;
	}

	ret = m5mols_write(sd, PARM_EFFECT, p_effect);
	if (!ret)
		ret = m5mols_write(sd, MON_EFFECT, m_effect);

	if (ret == 0 && m_effect == REG_COLOR_EFFECT_ON) {
		ret = m5mols_write(sd, MON_CFIXR, cfix_r);
		if (!ret)
			ret = m5mols_write(sd, MON_CFIXB, cfix_b);
	}

	v4l2_dbg(1, m5mols_debug, sd,
		 "p_effect: %#x, m_effect: %#x, r: %#x, b: %#x (%d)\n",
		 p_effect, m_effect, cfix_r, cfix_b, ret);

	return ret;
}