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
struct TYPE_8__ {int /*<<< orphan*/  length; scalar_t__ info; } ;
struct TYPE_7__ {TYPE_1__* parms; } ;
struct TYPE_6__ {int /*<<< orphan*/  length; scalar_t__ info; } ;
typedef  TYPE_2__ API_SAVE ;
typedef  TYPE_3__ API_PARSE ;

/* Variables and functions */

__attribute__((used)) static void api_load_msg(API_SAVE *in, API_PARSE *out)
{
	word i;

	i = 0;
	do
	{
		out[i].info = in->parms[i].info;
		out[i].length = in->parms[i].length;
	} while (in->parms[i++].info);
}