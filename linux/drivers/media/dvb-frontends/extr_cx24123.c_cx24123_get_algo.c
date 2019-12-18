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
struct dvb_frontend {int dummy; } ;
typedef  enum dvbfe_algo { ____Placeholder_dvbfe_algo } dvbfe_algo ;

/* Variables and functions */
 int DVBFE_ALGO_HW ; 

__attribute__((used)) static enum dvbfe_algo cx24123_get_algo(struct dvb_frontend *fe)
{
	return DVBFE_ALGO_HW;
}