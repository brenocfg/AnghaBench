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
typedef  int dword ;

/* Variables and functions */
 int CAPIDTMF_RECV_TOTAL_FREQUENCY_COUNT ; 

__attribute__((used)) static void capidtmf_goertzel_result(long *buffer, long *coeffs)
{
	int i;
	long d, e, q1, q2, lo, mid, hi;
	dword k;

	for (i = 0; i < CAPIDTMF_RECV_TOTAL_FREQUENCY_COUNT; i++)
	{
		q1 = buffer[i];
		q2 = buffer[i + CAPIDTMF_RECV_TOTAL_FREQUENCY_COUNT];
		d = coeffs[i] >> 1;
		if (d >= 0)
			d = ((d << 1) * (-q1 >> 16)) + (((dword)(((dword) d) * ((dword)(-q1 & 0xffff)))) >> 15);
		else
			d = ((-d << 1) * (-q1 >> 16)) + (((dword)(((dword) -d) * ((dword)(-q1 & 0xffff)))) >> 15);
		e = (q2 >= 0) ? q2 : -q2;
		if (d >= 0)
		{
			k = ((dword)(d & 0xffff)) * ((dword)(e & 0xffff));
			lo = k & 0xffff;
			mid = k >> 16;
			k = ((dword)(d >> 16)) * ((dword)(e & 0xffff));
			mid += k & 0xffff;
			hi = k >> 16;
			k = ((dword)(d & 0xffff)) * ((dword)(e >> 16));
			mid += k & 0xffff;
			hi += k >> 16;
			hi += ((dword)(d >> 16)) * ((dword)(e >> 16));
		}
		else
		{
			d = -d;
			k = ((dword)(d & 0xffff)) * ((dword)(e & 0xffff));
			lo = -((long)(k & 0xffff));
			mid = -((long)(k >> 16));
			k = ((dword)(d >> 16)) * ((dword)(e & 0xffff));
			mid -= k & 0xffff;
			hi = -((long)(k >> 16));
			k = ((dword)(d & 0xffff)) * ((dword)(e >> 16));
			mid -= k & 0xffff;
			hi -= k >> 16;
			hi -= ((dword)(d >> 16)) * ((dword)(e >> 16));
		}
		if (q2 < 0)
		{
			lo = -lo;
			mid = -mid;
			hi = -hi;
		}
		d = (q1 >= 0) ? q1 : -q1;
		k = ((dword)(d & 0xffff)) * ((dword)(d & 0xffff));
		lo += k & 0xffff;
		mid += k >> 16;
		k = ((dword)(d >> 16)) * ((dword)(d & 0xffff));
		mid += (k & 0xffff) << 1;
		hi += (k >> 16) << 1;
		hi += ((dword)(d >> 16)) * ((dword)(d >> 16));
		d = (q2 >= 0) ? q2 : -q2;
		k = ((dword)(d & 0xffff)) * ((dword)(d & 0xffff));
		lo += k & 0xffff;
		mid += k >> 16;
		k = ((dword)(d >> 16)) * ((dword)(d & 0xffff));
		mid += (k & 0xffff) << 1;
		hi += (k >> 16) << 1;
		hi += ((dword)(d >> 16)) * ((dword)(d >> 16));
		mid += lo >> 16;
		hi += mid >> 16;
		buffer[i] = (lo & 0xffff) | (mid << 16);
		buffer[i + CAPIDTMF_RECV_TOTAL_FREQUENCY_COUNT] = hi;
	}
}