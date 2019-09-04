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
struct trace_seq {int dummy; } ;

/* Variables and functions */
 unsigned int AC_ERR_ATA_BUS ; 
 unsigned int AC_ERR_DEV ; 
 unsigned int AC_ERR_HOST_BUS ; 
 unsigned int AC_ERR_HSM ; 
 unsigned int AC_ERR_INVALID ; 
 unsigned int AC_ERR_MEDIA ; 
 unsigned int AC_ERR_NCQ ; 
 unsigned int AC_ERR_NODEV_HINT ; 
 unsigned int AC_ERR_OTHER ; 
 unsigned int AC_ERR_SYSTEM ; 
 unsigned int AC_ERR_TIMEOUT ; 
 char* trace_seq_buffer_ptr (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,...) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,char) ; 

const char *
libata_trace_parse_eh_err_mask(struct trace_seq *p, unsigned int eh_err_mask)
{
	const char *ret = trace_seq_buffer_ptr(p);

	trace_seq_printf(p, "%x", eh_err_mask);
	if (eh_err_mask) {
		trace_seq_printf(p, "{ ");
		if (eh_err_mask & AC_ERR_DEV)
			trace_seq_printf(p, "DEV ");
		if (eh_err_mask & AC_ERR_HSM)
			trace_seq_printf(p, "HSM ");
		if (eh_err_mask & AC_ERR_TIMEOUT)
			trace_seq_printf(p, "TIMEOUT ");
		if (eh_err_mask & AC_ERR_MEDIA)
			trace_seq_printf(p, "MEDIA ");
		if (eh_err_mask & AC_ERR_ATA_BUS)
			trace_seq_printf(p, "ATA_BUS ");
		if (eh_err_mask & AC_ERR_HOST_BUS)
			trace_seq_printf(p, "HOST_BUS ");
		if (eh_err_mask & AC_ERR_SYSTEM)
			trace_seq_printf(p, "SYSTEM ");
		if (eh_err_mask & AC_ERR_INVALID)
			trace_seq_printf(p, "INVALID ");
		if (eh_err_mask & AC_ERR_OTHER)
			trace_seq_printf(p, "OTHER ");
		if (eh_err_mask & AC_ERR_NODEV_HINT)
			trace_seq_printf(p, "NODEV_HINT ");
		if (eh_err_mask & AC_ERR_NCQ)
			trace_seq_printf(p, "NCQ ");
		trace_seq_putc(p, '}');
	}
	trace_seq_putc(p, 0);

	return ret;
}