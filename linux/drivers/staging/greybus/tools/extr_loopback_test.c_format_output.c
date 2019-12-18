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
struct tm {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; } ;
struct loopback_test {char* test_name; int size; int iteration_max; scalar_t__ use_async; scalar_t__ porcelain; } ;
struct loopback_results {int error; int request_min; int request_max; double request_avg; int request_jitter; int throughput_min; int throughput_max; double throughput_avg; int throughput_jitter; int latency_min; int latency_max; double latency_avg; int latency_jitter; int apbridge_unipro_latency_min; int apbridge_unipro_latency_max; double apbridge_unipro_latency_avg; int apbridge_unipro_latency_jitter; int gbphy_firmware_latency_min; int gbphy_firmware_latency_max; double gbphy_firmware_latency_avg; int gbphy_firmware_latency_jitter; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int snprintf (char*,int,char*,...) ; 

int format_output(struct loopback_test *t,
		  struct loopback_results *r,
		  const char *dev_name,
		  char *buf, int buf_len,
		  struct tm *tm)
{
	int len = 0;

	memset(buf, 0x00, buf_len);
	len = snprintf(buf, buf_len, "%u-%u-%u %u:%u:%u",
		       tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
		       tm->tm_hour, tm->tm_min, tm->tm_sec);

	if (t->porcelain) {
		len += snprintf(&buf[len], buf_len - len,
			"\n test:\t\t\t%s\n path:\t\t\t%s\n size:\t\t\t%u\n iterations:\t\t%u\n errors:\t\t%u\n async:\t\t\t%s\n",
			t->test_name,
			dev_name,
			t->size,
			t->iteration_max,
			r->error,
			t->use_async ? "Enabled" : "Disabled");

		len += snprintf(&buf[len], buf_len - len,
			" requests per-sec:\tmin=%u, max=%u, average=%f, jitter=%u\n",
			r->request_min,
			r->request_max,
			r->request_avg,
			r->request_jitter);

		len += snprintf(&buf[len], buf_len - len,
			" ap-throughput B/s:\tmin=%u max=%u average=%f jitter=%u\n",
			r->throughput_min,
			r->throughput_max,
			r->throughput_avg,
			r->throughput_jitter);
		len += snprintf(&buf[len], buf_len - len,
			" ap-latency usec:\tmin=%u max=%u average=%f jitter=%u\n",
			r->latency_min,
			r->latency_max,
			r->latency_avg,
			r->latency_jitter);
		len += snprintf(&buf[len], buf_len - len,
			" apbridge-latency usec:\tmin=%u max=%u average=%f jitter=%u\n",
			r->apbridge_unipro_latency_min,
			r->apbridge_unipro_latency_max,
			r->apbridge_unipro_latency_avg,
			r->apbridge_unipro_latency_jitter);

		len += snprintf(&buf[len], buf_len - len,
			" gbphy-latency usec:\tmin=%u max=%u average=%f jitter=%u\n",
			r->gbphy_firmware_latency_min,
			r->gbphy_firmware_latency_max,
			r->gbphy_firmware_latency_avg,
			r->gbphy_firmware_latency_jitter);

	} else {
		len += snprintf(&buf[len], buf_len - len, ",%s,%s,%u,%u,%u",
			t->test_name, dev_name, t->size, t->iteration_max,
			r->error);

		len += snprintf(&buf[len], buf_len - len, ",%u,%u,%f,%u",
			r->request_min,
			r->request_max,
			r->request_avg,
			r->request_jitter);

		len += snprintf(&buf[len], buf_len - len, ",%u,%u,%f,%u",
			r->latency_min,
			r->latency_max,
			r->latency_avg,
			r->latency_jitter);

		len += snprintf(&buf[len], buf_len - len, ",%u,%u,%f,%u",
			r->throughput_min,
			r->throughput_max,
			r->throughput_avg,
			r->throughput_jitter);

		len += snprintf(&buf[len], buf_len - len, ",%u,%u,%f,%u",
			r->apbridge_unipro_latency_min,
			r->apbridge_unipro_latency_max,
			r->apbridge_unipro_latency_avg,
			r->apbridge_unipro_latency_jitter);

		len += snprintf(&buf[len], buf_len - len, ",%u,%u,%f,%u",
			r->gbphy_firmware_latency_min,
			r->gbphy_firmware_latency_max,
			r->gbphy_firmware_latency_avg,
			r->gbphy_firmware_latency_jitter);
	}

	printf("\n%s\n", buf);

	return len;
}