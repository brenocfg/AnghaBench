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
typedef  enum dm9000_type { ____Placeholder_dm9000_type } dm9000_type ;

/* Variables and functions */
#define  TYPE_DM9000A 130 
#define  TYPE_DM9000B 129 
#define  TYPE_DM9000E 128 

__attribute__((used)) static unsigned char dm9000_type_to_char(enum dm9000_type type)
{
	switch (type) {
	case TYPE_DM9000E: return 'e';
	case TYPE_DM9000A: return 'a';
	case TYPE_DM9000B: return 'b';
	}

	return '?';
}