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
typedef  enum madera_type { ____Placeholder_madera_type } madera_type ;

/* Variables and functions */
#define  CS42L92 136 
#define  CS47L15 135 
#define  CS47L35 134 
#define  CS47L85 133 
#define  CS47L90 132 
#define  CS47L91 131 
#define  CS47L92 130 
#define  CS47L93 129 
#define  WM1840 128 

const char *madera_name_from_type(enum madera_type type)
{
	switch (type) {
	case CS47L15:
		return "CS47L15";
	case CS47L35:
		return "CS47L35";
	case CS47L85:
		return "CS47L85";
	case CS47L90:
		return "CS47L90";
	case CS47L91:
		return "CS47L91";
	case CS42L92:
		return "CS42L92";
	case CS47L92:
		return "CS47L92";
	case CS47L93:
		return "CS47L93";
	case WM1840:
		return "WM1840";
	default:
		return "Unknown";
	}
}