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
typedef  int ssize_t ;
typedef  long long s64 ;

/* Variables and functions */
#define  IIO_VAL_FRACTIONAL 134 
#define  IIO_VAL_FRACTIONAL_LOG2 133 
#define  IIO_VAL_INT 132 
#define  IIO_VAL_INT_MULTIPLE 131 
#define  IIO_VAL_INT_PLUS_MICRO 130 
#define  IIO_VAL_INT_PLUS_MICRO_DB 129 
#define  IIO_VAL_INT_PLUS_NANO 128 
 int abs (int const) ; 
 unsigned long long div_s64 (long long,int const) ; 
 scalar_t__ div_s64_rem (unsigned long long,long long,int*) ; 
 unsigned long long shift_right (long long,int const) ; 
 int snprintf (char*,size_t,char*,int const,...) ; 

__attribute__((used)) static ssize_t __iio_format_value(char *buf, size_t len, unsigned int type,
				  int size, const int *vals)
{
	unsigned long long tmp;
	int tmp0, tmp1;
	bool scale_db = false;

	switch (type) {
	case IIO_VAL_INT:
		return snprintf(buf, len, "%d", vals[0]);
	case IIO_VAL_INT_PLUS_MICRO_DB:
		scale_db = true;
		/* fall through */
	case IIO_VAL_INT_PLUS_MICRO:
		if (vals[1] < 0)
			return snprintf(buf, len, "-%d.%06u%s", abs(vals[0]),
					-vals[1], scale_db ? " dB" : "");
		else
			return snprintf(buf, len, "%d.%06u%s", vals[0], vals[1],
					scale_db ? " dB" : "");
	case IIO_VAL_INT_PLUS_NANO:
		if (vals[1] < 0)
			return snprintf(buf, len, "-%d.%09u", abs(vals[0]),
					-vals[1]);
		else
			return snprintf(buf, len, "%d.%09u", vals[0], vals[1]);
	case IIO_VAL_FRACTIONAL:
		tmp = div_s64((s64)vals[0] * 1000000000LL, vals[1]);
		tmp1 = vals[1];
		tmp0 = (int)div_s64_rem(tmp, 1000000000, &tmp1);
		return snprintf(buf, len, "%d.%09u", tmp0, abs(tmp1));
	case IIO_VAL_FRACTIONAL_LOG2:
		tmp = shift_right((s64)vals[0] * 1000000000LL, vals[1]);
		tmp0 = (int)div_s64_rem(tmp, 1000000000LL, &tmp1);
		return snprintf(buf, len, "%d.%09u", tmp0, abs(tmp1));
	case IIO_VAL_INT_MULTIPLE:
	{
		int i;
		int l = 0;

		for (i = 0; i < size; ++i) {
			l += snprintf(&buf[l], len - l, "%d ", vals[i]);
			if (l >= len)
				break;
		}
		return l;
	}
	default:
		return 0;
	}
}