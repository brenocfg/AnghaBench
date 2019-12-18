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
typedef  enum param_type { ____Placeholder_param_type } param_type ;

/* Variables and functions */
#define  TUNER_PARAM_TYPE_DIGITAL 132 
#define  TUNER_PARAM_TYPE_NTSC 131 
#define  TUNER_PARAM_TYPE_PAL 130 
#define  TUNER_PARAM_TYPE_RADIO 129 
#define  TUNER_PARAM_TYPE_SECAM 128 

__attribute__((used)) static inline char *tuner_param_name(enum param_type type)
{
	char *name;

	switch (type) {
	case TUNER_PARAM_TYPE_RADIO:
		name = "radio";
		break;
	case TUNER_PARAM_TYPE_PAL:
		name = "pal";
		break;
	case TUNER_PARAM_TYPE_SECAM:
		name = "secam";
		break;
	case TUNER_PARAM_TYPE_NTSC:
		name = "ntsc";
		break;
	case TUNER_PARAM_TYPE_DIGITAL:
		name = "digital";
		break;
	default:
		name = "unknown";
		break;
	}
	return name;
}