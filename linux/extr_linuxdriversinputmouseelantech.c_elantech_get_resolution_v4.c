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
struct psmouse {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETP_RESOLUTION_QUERY ; 
 unsigned int elantech_convert_res (unsigned char) ; 
 scalar_t__ elantech_send_cmd (struct psmouse*,int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static int elantech_get_resolution_v4(struct psmouse *psmouse,
				      unsigned int *x_res,
				      unsigned int *y_res,
				      unsigned int *bus)
{
	unsigned char param[3];

	if (elantech_send_cmd(psmouse, ETP_RESOLUTION_QUERY, param))
		return -1;

	*x_res = elantech_convert_res(param[1] & 0x0f);
	*y_res = elantech_convert_res((param[1] & 0xf0) >> 4);
	*bus = param[2];

	return 0;
}