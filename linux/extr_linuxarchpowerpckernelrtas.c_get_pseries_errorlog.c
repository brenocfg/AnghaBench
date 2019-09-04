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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct rtas_ext_event_log_v6 {unsigned char* vendor_log; } ;
struct rtas_error_log {unsigned char* buffer; } ;
struct pseries_errorlog {int dummy; } ;

/* Variables and functions */
 int RTAS_V6EXT_COMPANY_ID_IBM ; 
 scalar_t__ RTAS_V6EXT_LOG_FORMAT_EVENT_LOG ; 
 scalar_t__ pseries_errorlog_id (struct pseries_errorlog*) ; 
 int /*<<< orphan*/  pseries_errorlog_length (struct pseries_errorlog*) ; 
 int rtas_error_extended_log_length (struct rtas_error_log*) ; 
 int rtas_ext_event_company_id (struct rtas_ext_event_log_v6*) ; 
 scalar_t__ rtas_ext_event_log_format (struct rtas_ext_event_log_v6*) ; 

struct pseries_errorlog *get_pseries_errorlog(struct rtas_error_log *log,
					      uint16_t section_id)
{
	struct rtas_ext_event_log_v6 *ext_log =
		(struct rtas_ext_event_log_v6 *)log->buffer;
	struct pseries_errorlog *sect;
	unsigned char *p, *log_end;
	uint32_t ext_log_length = rtas_error_extended_log_length(log);
	uint8_t log_format = rtas_ext_event_log_format(ext_log);
	uint32_t company_id = rtas_ext_event_company_id(ext_log);

	/* Check that we understand the format */
	if (ext_log_length < sizeof(struct rtas_ext_event_log_v6) ||
	    log_format != RTAS_V6EXT_LOG_FORMAT_EVENT_LOG ||
	    company_id != RTAS_V6EXT_COMPANY_ID_IBM)
		return NULL;

	log_end = log->buffer + ext_log_length;
	p = ext_log->vendor_log;

	while (p < log_end) {
		sect = (struct pseries_errorlog *)p;
		if (pseries_errorlog_id(sect) == section_id)
			return sect;
		p += pseries_errorlog_length(sect);
	}

	return NULL;
}