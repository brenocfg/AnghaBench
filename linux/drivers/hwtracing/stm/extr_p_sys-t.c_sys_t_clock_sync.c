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
typedef  unsigned char const u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct stm_data {scalar_t__ (* packet ) (struct stm_data*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned char const*) ;} ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  payload ;
typedef  int /*<<< orphan*/  header ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_SYNC_HEADER ; 
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 int /*<<< orphan*/  STP_PACKET_DATA ; 
 int /*<<< orphan*/  STP_PACKET_FLAG ; 
 int /*<<< orphan*/  STP_PACKET_TIMESTAMPED ; 
 int /*<<< orphan*/  ktime_get_real_ns () ; 
 scalar_t__ stm_data_write (struct stm_data*,unsigned int,unsigned int,int,int /*<<< orphan*/ **,int) ; 
 scalar_t__ stub1 (struct stm_data*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned char const*) ; 
 scalar_t__ stub2 (struct stm_data*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned char const*) ; 

__attribute__((used)) static ssize_t
sys_t_clock_sync(struct stm_data *data, unsigned int m, unsigned int c)
{
	u32 header = CLOCK_SYNC_HEADER;
	const unsigned char nil = 0;
	u64 payload[2]; /* Clock value and frequency */
	ssize_t sz;

	sz = data->packet(data, m, c, STP_PACKET_DATA, STP_PACKET_TIMESTAMPED,
			  4, (u8 *)&header);
	if (sz <= 0)
		return sz;

	payload[0] = ktime_get_real_ns();
	payload[1] = NSEC_PER_SEC;
	sz = stm_data_write(data, m, c, false, &payload, sizeof(payload));
	if (sz <= 0)
		return sz;

	data->packet(data, m, c, STP_PACKET_FLAG, 0, 0, &nil);

	return sizeof(header) + sizeof(payload);
}