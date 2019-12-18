#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int noprobe; } ;

/* Variables and functions */
 size_t CARDU1 ; 
 size_t CARDU2 ; 
 TYPE_1__* cardu_sockets ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int vrc4173_cardu_setup(char *options)
{
	if (options == NULL || *options == '\0')
		return 1;

	if (strncmp(options, "cardu1:", 7) == 0) {
		options += 7;
		if (*options != '\0') {
			if (strncmp(options, "noprobe", 7) == 0) {
				cardu_sockets[CARDU1].noprobe = 1;
				options += 7;
			}

			if (*options != ',')
				return 1;
		} else
			return 1;
	}

	if (strncmp(options, "cardu2:", 7) == 0) {
		options += 7;
		if ((*options != '\0') && (strncmp(options, "noprobe", 7) == 0))
			cardu_sockets[CARDU2].noprobe = 1;
	}

	return 1;
}