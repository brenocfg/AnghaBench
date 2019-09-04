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
typedef  int /*<<< orphan*/  u8 ;
struct dvb_demux {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _dvb_dmx_swfilter (struct dvb_demux*,int /*<<< orphan*/  const*,size_t,int) ; 

void dvb_dmx_swfilter_204(struct dvb_demux *demux, const u8 *buf, size_t count)
{
	_dvb_dmx_swfilter(demux, buf, count, 204);
}