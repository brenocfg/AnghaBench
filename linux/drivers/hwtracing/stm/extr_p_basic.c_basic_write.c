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
struct stm_output {unsigned int channel; unsigned int master; } ;
struct stm_data {int /*<<< orphan*/  (* packet ) (struct stm_data*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char const*) ;} ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  STP_PACKET_FLAG ; 
 scalar_t__ stm_data_write (struct stm_data*,unsigned int,unsigned int,int,char const*,size_t) ; 
 int /*<<< orphan*/  stub1 (struct stm_data*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char const*) ; 

__attribute__((used)) static ssize_t basic_write(struct stm_data *data, struct stm_output *output,
			   unsigned int chan, const char *buf, size_t count)
{
	unsigned int c = output->channel + chan;
	unsigned int m = output->master;
	const unsigned char nil = 0;
	ssize_t sz;

	sz = stm_data_write(data, m, c, true, buf, count);
	if (sz > 0)
		data->packet(data, m, c, STP_PACKET_FLAG, 0, 0, &nil);

	return sz;
}