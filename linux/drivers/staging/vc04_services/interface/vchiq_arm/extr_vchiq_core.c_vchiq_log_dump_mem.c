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
typedef  char u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  VCHIQ_LOG_TRACE ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  vchiq_log_trace (int /*<<< orphan*/ ,char*,char const*,char*,...) ; 

void vchiq_log_dump_mem(const char *label, u32 addr, const void *void_mem,
	size_t num_bytes)
{
	const u8  *mem = void_mem;
	size_t          offset;
	char            line_buf[100];
	char           *s;

	while (num_bytes > 0) {
		s = line_buf;

		for (offset = 0; offset < 16; offset++) {
			if (offset < num_bytes)
				s += scnprintf(s, 4, "%02x ", mem[offset]);
			else
				s += scnprintf(s, 4, "   ");
		}

		for (offset = 0; offset < 16; offset++) {
			if (offset < num_bytes) {
				u8 ch = mem[offset];

				if ((ch < ' ') || (ch > '~'))
					ch = '.';
				*s++ = (char)ch;
			}
		}
		*s++ = '\0';

		if ((label != NULL) && (*label != '\0'))
			vchiq_log_trace(VCHIQ_LOG_TRACE,
				"%s: %08x: %s", label, addr, line_buf);
		else
			vchiq_log_trace(VCHIQ_LOG_TRACE,
				"%08x: %s", addr, line_buf);

		addr += 16;
		mem += 16;
		if (num_bytes > 16)
			num_bytes -= 16;
		else
			num_bytes = 0;
	}
}