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
struct baycom_state {int options; } ;

/* Variables and functions */
 int BAYCOM_OPTIONS_SOFTDCD ; 
 int /*<<< orphan*/  strchr (char const*,char) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static int baycom_setmode(struct baycom_state *bc, const char *modestr)
{
	if (!strncmp(modestr, "picpar", 6))
		bc->options = 0;
	else if (!strncmp(modestr, "par96", 5))
		bc->options = BAYCOM_OPTIONS_SOFTDCD;
	else
		bc->options = !!strchr(modestr, '*');
	return 0;
}