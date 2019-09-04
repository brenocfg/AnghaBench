#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t word ;
typedef  char byte ;
struct TYPE_8__ {int /*<<< orphan*/ * info; scalar_t__ length; } ;
struct TYPE_7__ {char* info; TYPE_1__* parms; } ;
struct TYPE_6__ {char* info; scalar_t__ length; } ;
typedef  TYPE_2__ API_SAVE ;
typedef  TYPE_3__ API_PARSE ;

/* Variables and functions */

__attribute__((used)) static void api_save_msg(API_PARSE *in, byte *format, API_SAVE *out)
{
	word i, j, n = 0;
	byte *p;

	p = out->info;
	for (i = 0; format[i] != '\0'; i++)
	{
		out->parms[i].info = p;
		out->parms[i].length = in[i].length;
		switch (format[i])
		{
		case 'b':
			n = 1;
			break;
		case 'w':
			n = 2;
			break;
		case 'd':
			n = 4;
			break;
		case 's':
			n = in[i].length + 1;
			break;
		}
		for (j = 0; j < n; j++)
			*(p++) = in[i].info[j];
	}
	out->parms[i].info = NULL;
	out->parms[i].length = 0;
}