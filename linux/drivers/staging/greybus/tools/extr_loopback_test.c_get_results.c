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
struct loopback_results {void* gbphy_firmware_latency_min; void* gbphy_firmware_latency_max; void* gbphy_firmware_latency_jitter; void* apbridge_unipro_latency_min; void* apbridge_unipro_latency_max; void* apbridge_unipro_latency_jitter; void* throughput_min; void* throughput_max; void* throughput_jitter; void* latency_min; void* latency_max; void* latency_jitter; void* request_min; void* request_max; void* request_jitter; void* gbphy_firmware_latency_avg; void* apbridge_unipro_latency_avg; void* throughput_avg; void* latency_avg; void* request_avg; void* error; } ;
struct loopback_test {int device_count; struct loopback_results aggregate_results; scalar_t__ aggregate_output; struct loopback_device* devices; } ;
struct loopback_device {int /*<<< orphan*/  sysfs_entry; struct loopback_results results; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_enabled (struct loopback_test*,int) ; 
 void* get_apbridge_unipro_latency_avg_aggregate (struct loopback_test*) ; 
 void* get_apbridge_unipro_latency_max_aggregate (struct loopback_test*) ; 
 void* get_apbridge_unipro_latency_min_aggregate (struct loopback_test*) ; 
 void* get_gbphy_firmware_latency_avg_aggregate (struct loopback_test*) ; 
 void* get_gbphy_firmware_latency_max_aggregate (struct loopback_test*) ; 
 void* get_gbphy_firmware_latency_min_aggregate (struct loopback_test*) ; 
 void* get_latency_avg_aggregate (struct loopback_test*) ; 
 void* get_latency_max_aggregate (struct loopback_test*) ; 
 void* get_latency_min_aggregate (struct loopback_test*) ; 
 void* get_request_avg_aggregate (struct loopback_test*) ; 
 void* get_request_max_aggregate (struct loopback_test*) ; 
 void* get_request_min_aggregate (struct loopback_test*) ; 
 void* get_throughput_avg_aggregate (struct loopback_test*) ; 
 void* get_throughput_max_aggregate (struct loopback_test*) ; 
 void* get_throughput_min_aggregate (struct loopback_test*) ; 
 void* read_sysfs_float (int /*<<< orphan*/ ,char*) ; 
 void* read_sysfs_int (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int get_results(struct loopback_test *t)
{
	struct loopback_device *d;
	struct loopback_results *r;
	int i;

	for (i = 0; i < t->device_count; i++) {
		if (!device_enabled(t, i))
			continue;

		d = &t->devices[i];
		r = &d->results;

		r->error = read_sysfs_int(d->sysfs_entry, "error");
		r->request_min = read_sysfs_int(d->sysfs_entry, "requests_per_second_min");
		r->request_max = read_sysfs_int(d->sysfs_entry, "requests_per_second_max");
		r->request_avg = read_sysfs_float(d->sysfs_entry, "requests_per_second_avg");

		r->latency_min = read_sysfs_int(d->sysfs_entry, "latency_min");
		r->latency_max = read_sysfs_int(d->sysfs_entry, "latency_max");
		r->latency_avg = read_sysfs_float(d->sysfs_entry, "latency_avg");

		r->throughput_min = read_sysfs_int(d->sysfs_entry, "throughput_min");
		r->throughput_max = read_sysfs_int(d->sysfs_entry, "throughput_max");
		r->throughput_avg = read_sysfs_float(d->sysfs_entry, "throughput_avg");

		r->apbridge_unipro_latency_min =
			read_sysfs_int(d->sysfs_entry, "apbridge_unipro_latency_min");
		r->apbridge_unipro_latency_max =
			read_sysfs_int(d->sysfs_entry, "apbridge_unipro_latency_max");
		r->apbridge_unipro_latency_avg =
			read_sysfs_float(d->sysfs_entry, "apbridge_unipro_latency_avg");

		r->gbphy_firmware_latency_min =
			read_sysfs_int(d->sysfs_entry, "gbphy_firmware_latency_min");
		r->gbphy_firmware_latency_max =
			read_sysfs_int(d->sysfs_entry, "gbphy_firmware_latency_max");
		r->gbphy_firmware_latency_avg =
			read_sysfs_float(d->sysfs_entry, "gbphy_firmware_latency_avg");

		r->request_jitter = r->request_max - r->request_min;
		r->latency_jitter = r->latency_max - r->latency_min;
		r->throughput_jitter = r->throughput_max - r->throughput_min;
		r->apbridge_unipro_latency_jitter =
			r->apbridge_unipro_latency_max - r->apbridge_unipro_latency_min;
		r->gbphy_firmware_latency_jitter =
			r->gbphy_firmware_latency_max - r->gbphy_firmware_latency_min;

	}

	/*calculate the aggregate results of all enabled devices */
	if (t->aggregate_output) {
		r = &t->aggregate_results;

		r->request_min = get_request_min_aggregate(t);
		r->request_max = get_request_max_aggregate(t);
		r->request_avg = get_request_avg_aggregate(t);

		r->latency_min = get_latency_min_aggregate(t);
		r->latency_max = get_latency_max_aggregate(t);
		r->latency_avg = get_latency_avg_aggregate(t);

		r->throughput_min = get_throughput_min_aggregate(t);
		r->throughput_max = get_throughput_max_aggregate(t);
		r->throughput_avg = get_throughput_avg_aggregate(t);

		r->apbridge_unipro_latency_min =
			get_apbridge_unipro_latency_min_aggregate(t);
		r->apbridge_unipro_latency_max =
			get_apbridge_unipro_latency_max_aggregate(t);
		r->apbridge_unipro_latency_avg =
			get_apbridge_unipro_latency_avg_aggregate(t);

		r->gbphy_firmware_latency_min =
			get_gbphy_firmware_latency_min_aggregate(t);
		r->gbphy_firmware_latency_max =
			get_gbphy_firmware_latency_max_aggregate(t);
		r->gbphy_firmware_latency_avg =
			get_gbphy_firmware_latency_avg_aggregate(t);

		r->request_jitter = r->request_max - r->request_min;
		r->latency_jitter = r->latency_max - r->latency_min;
		r->throughput_jitter = r->throughput_max - r->throughput_min;
		r->apbridge_unipro_latency_jitter =
			r->apbridge_unipro_latency_max - r->apbridge_unipro_latency_min;
		r->gbphy_firmware_latency_jitter =
			r->gbphy_firmware_latency_max - r->gbphy_firmware_latency_min;

	}

	return 0;
}