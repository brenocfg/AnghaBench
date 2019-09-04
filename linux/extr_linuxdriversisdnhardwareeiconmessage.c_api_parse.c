#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t word ;
typedef  int byte ;
struct TYPE_3__ {int* info; int length; } ;
typedef  TYPE_1__ API_PARSE ;

/* Variables and functions */

__attribute__((used)) static word api_parse(byte *msg, word length, byte *format, API_PARSE *parms)
{
	word i;
	word p;

	for (i = 0, p = 0; format[i]; i++) {
		if (parms)
		{
			parms[i].info = &msg[p];
		}
		switch (format[i]) {
		case 'b':
			p += 1;
			break;
		case 'w':
			p += 2;
			break;
		case 'd':
			p += 4;
			break;
		case 's':
			if (msg[p] == 0xff) {
				parms[i].info += 2;
				parms[i].length = msg[p + 1] + (msg[p + 2] << 8);
				p += (parms[i].length + 3);
			}
			else {
				parms[i].length = msg[p];
				p += (parms[i].length + 1);
			}
			break;
		}

		if (p > length) return true;
	}
	if (parms) parms[i].info = NULL;
	return false;
}