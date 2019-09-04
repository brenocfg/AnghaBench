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
struct smsdvb_debugfs {int stats_count; char* stats_data; int /*<<< orphan*/  stats_queue; int /*<<< orphan*/  lock; } ;
struct sms_stats {int is_rf_locked; int is_demod_locked; int is_external_lna_on; int SNR; int ber; int FIB_CRC; int ts_per; int MFER; int RSSI; int in_band_pwr; int carrier_offset; int modem_state; int frequency; int bandwidth; int transmission_mode; int guard_interval; int code_rate; int lp_code_rate; int hierarchy; int constellation; int burst_size; int burst_duration; int burst_cycle_time; int calc_burst_cycle_time; int num_of_rows; int num_of_padd_cols; int num_of_punct_cols; int error_ts_packets; int total_ts_packets; int num_of_valid_mpe_tlbs; int num_of_invalid_mpe_tlbs; int num_of_corrected_mpe_tlbs; int ber_error_count; int ber_bit_count; int sms_to_host_tx_errors; int pre_ber; int cell_id; int dvbh_srv_ind_hp; int dvbh_srv_ind_lp; int num_mpe_received; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ snprintf (char*,scalar_t__,char*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smsdvb_print_dvb_stats(struct smsdvb_debugfs *debug_data,
			    struct sms_stats *p)
{
	int n = 0;
	char *buf;

	spin_lock(&debug_data->lock);
	if (debug_data->stats_count) {
		spin_unlock(&debug_data->lock);
		return;
	}

	buf = debug_data->stats_data;

	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "is_rf_locked = %d\n", p->is_rf_locked);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "is_demod_locked = %d\n", p->is_demod_locked);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "is_external_lna_on = %d\n", p->is_external_lna_on);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "SNR = %d\n", p->SNR);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "ber = %d\n", p->ber);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "FIB_CRC = %d\n", p->FIB_CRC);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "ts_per = %d\n", p->ts_per);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "MFER = %d\n", p->MFER);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "RSSI = %d\n", p->RSSI);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "in_band_pwr = %d\n", p->in_band_pwr);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "carrier_offset = %d\n", p->carrier_offset);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "modem_state = %d\n", p->modem_state);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "frequency = %d\n", p->frequency);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "bandwidth = %d\n", p->bandwidth);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "transmission_mode = %d\n", p->transmission_mode);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "modem_state = %d\n", p->modem_state);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "guard_interval = %d\n", p->guard_interval);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "code_rate = %d\n", p->code_rate);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "lp_code_rate = %d\n", p->lp_code_rate);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "hierarchy = %d\n", p->hierarchy);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "constellation = %d\n", p->constellation);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "burst_size = %d\n", p->burst_size);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "burst_duration = %d\n", p->burst_duration);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "burst_cycle_time = %d\n", p->burst_cycle_time);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "calc_burst_cycle_time = %d\n",
		      p->calc_burst_cycle_time);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "num_of_rows = %d\n", p->num_of_rows);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "num_of_padd_cols = %d\n", p->num_of_padd_cols);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "num_of_punct_cols = %d\n", p->num_of_punct_cols);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "error_ts_packets = %d\n", p->error_ts_packets);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "total_ts_packets = %d\n", p->total_ts_packets);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "num_of_valid_mpe_tlbs = %d\n", p->num_of_valid_mpe_tlbs);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "num_of_invalid_mpe_tlbs = %d\n", p->num_of_invalid_mpe_tlbs);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "num_of_corrected_mpe_tlbs = %d\n", p->num_of_corrected_mpe_tlbs);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "ber_error_count = %d\n", p->ber_error_count);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "ber_bit_count = %d\n", p->ber_bit_count);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "sms_to_host_tx_errors = %d\n", p->sms_to_host_tx_errors);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "pre_ber = %d\n", p->pre_ber);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "cell_id = %d\n", p->cell_id);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "dvbh_srv_ind_hp = %d\n", p->dvbh_srv_ind_hp);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "dvbh_srv_ind_lp = %d\n", p->dvbh_srv_ind_lp);
	n += snprintf(&buf[n], PAGE_SIZE - n,
		      "num_mpe_received = %d\n", p->num_mpe_received);

	debug_data->stats_count = n;
	spin_unlock(&debug_data->lock);
	wake_up(&debug_data->stats_queue);
}