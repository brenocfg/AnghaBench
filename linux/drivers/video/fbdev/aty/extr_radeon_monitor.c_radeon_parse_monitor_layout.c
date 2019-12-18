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
struct radeonfb_info {void* mon2_type; void* mon1_type; } ;

/* Variables and functions */
 void* MT_CRT ; 
 void* MT_DFP ; 
 void* MT_LCD ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int radeon_parse_monitor_layout(struct radeonfb_info *rinfo,
				       const char *monitor_layout)
{
	char s1[5], s2[5];
	int i = 0, second = 0;
	const char *s;

	if (!monitor_layout)
		return 0;

	s = monitor_layout;
	do {
		switch(*s) {
		case ',':
			s1[i] = '\0';
			i = 0;
			second = 1;
			break;
		case ' ':
		case '\0':
			break;
		default:
			if (i > 4)
				break;
			if (second)
				s2[i] = *s;
			else
				s1[i] = *s;
			i++;
		}

		if (i > 4)
			i = 4;

	} while (*s++);
	if (second)
		s2[i] = 0;
	else {
		s1[i] = 0;
		s2[0] = 0;
	}
	if (strcmp(s1, "CRT") == 0)
		rinfo->mon1_type = MT_CRT;
	else if (strcmp(s1, "TMDS") == 0)
		rinfo->mon1_type = MT_DFP;
	else if (strcmp(s1, "LVDS") == 0)
		rinfo->mon1_type = MT_LCD;

	if (strcmp(s2, "CRT") == 0)
		rinfo->mon2_type = MT_CRT;
	else if (strcmp(s2, "TMDS") == 0)
		rinfo->mon2_type = MT_DFP;
	else if (strcmp(s2, "LVDS") == 0)
		rinfo->mon2_type = MT_LCD;

	return 1;
}