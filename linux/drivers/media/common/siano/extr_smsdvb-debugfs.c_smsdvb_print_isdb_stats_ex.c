#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct smsdvb_debugfs {int stats_count; char* stats_data; int /*<<< orphan*/  stats_queue; int /*<<< orphan*/  lock; } ;
struct sms_isdbt_stats_ex {int statistics_type; int full_size; int is_rf_locked; int is_demod_locked; int is_external_lna_on; int SNR; int RSSI; int in_band_pwr; int carrier_offset; int bandwidth; int frequency; int transmission_mode; int modem_state; int guard_interval; int system_type; int partial_reception; int num_of_layers; int segment_number; int tune_bw; TYPE_1__* layer_info; } ;
struct TYPE_2__ {int number_of_segments; int code_rate; int constellation; int ber; int ber_error_count; int ber_bit_count; int pre_ber; int ts_per; int error_ts_packets; int total_ts_packets; int ti_ldepth_i; int tmcc_errors; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ snprintf (char*,scalar_t__,char*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smsdvb_print_isdb_stats_ex(struct smsdvb_debugfs *debug_data,
				struct sms_isdbt_stats_ex *p)
{
	int i, n = 0;
	char *buf;

	spin_lock(&debug_data->lock);
	if (debug_data->stats_count) {
		spin_unlock(&debug_data->lock);
		return;
	}

	buf = debug_data->stats_data;

	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "statistics_type = %d\t", p->statistics_type);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "full_size = %d\n", p->full_size);

	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "is_rf_locked = %d\t\t", p->is_rf_locked);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "is_demod_locked = %d\t", p->is_demod_locked);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "is_external_lna_on = %d\n", p->is_external_lna_on);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "SNR = %d dB\t\t", p->SNR);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "RSSI = %d dBm\t\t", p->RSSI);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "in_band_pwr = %d dBm\n", p->in_band_pwr);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "carrier_offset = %d\t", p->carrier_offset);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "bandwidth = %d\t\t", p->bandwidth);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "frequency = %d Hz\n", p->frequency);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "transmission_mode = %d\t", p->transmission_mode);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "modem_state = %d\t\t", p->modem_state);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "guard_interval = %d\n", p->guard_interval);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "system_type = %d\t\t", p->system_type);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "partial_reception = %d\t", p->partial_reception);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "num_of_layers = %d\n", p->num_of_layers);
	n += snprintf(&buf[n], PAGE_SIZE - n, "segment_number = %d\t",
		      p->segment_number);
	n += snprintf(&buf[n], PAGE_SIZE - n, "tune_bw = %d\n",
		      p->tune_bw);

	for (i = 0; i < 3; i++) {
		if (p->layer_info[i].number_of_segments < 1 ||
		    p->layer_info[i].number_of_segments > 13)
			continue;

		n += snprintf(&buf[n], PAGE_SIZE - n, "\nLayer %d\n", i);
		n += snprintf(&buf[n], PAGE_SIZE - n, "\tcode_rate = %d\t",
			      p->layer_info[i].code_rate);
		n += snprintf(&buf[n], PAGE_SIZE - n, "constellation = %d\n",
			      p->layer_info[i].constellation);
		n += snprintf(&buf[n], PAGE_SIZE - n, "\tber = %-5d\t",
			      p->layer_info[i].ber);
		n += snprintf(&buf[n], PAGE_SIZE - n, "\tber_error_count = %-5d\t",
			      p->layer_info[i].ber_error_count);
		n += snprintf(&buf[n], PAGE_SIZE - n, "ber_bit_count = %-5d\n",
			      p->layer_info[i].ber_bit_count);
		n += snprintf(&buf[n], PAGE_SIZE - n, "\tpre_ber = %-5d\t",
			      p->layer_info[i].pre_ber);
		n += snprintf(&buf[n], PAGE_SIZE - n, "\tts_per = %-5d\n",
			      p->layer_info[i].ts_per);
		n += snprintf(&buf[n], PAGE_SIZE - n, "\terror_ts_packets = %-5d\t",
			      p->layer_info[i].error_ts_packets);
		n += snprintf(&buf[n], PAGE_SIZE - n, "total_ts_packets = %-5d\t",
			      p->layer_info[i].total_ts_packets);
		n += snprintf(&buf[n], PAGE_SIZE - n, "ti_ldepth_i = %d\n",
			      p->layer_info[i].ti_ldepth_i);
		n += snprintf(&buf[n], PAGE_SIZE - n,
			      "\tnumber_of_segments = %d\t",
			      p->layer_info[i].number_of_segments);
		n += snprintf(&buf[n], PAGE_SIZE - n, "tmcc_errors = %d\n",
			      p->layer_info[i].tmcc_errors);
	}


	debug_data->stats_count = n;
	spin_unlock(&debug_data->lock);

	wake_up(&debug_data->stats_queue);
}