#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_4__ {unsigned int len; int* msg; } ;
struct TYPE_3__ {int* msg; int /*<<< orphan*/  len; } ;
struct cec_pin {int state; int tx_nacked; int tx_bit; int tx_extra_bytes; int tx_post_eom; int rx_bit; TYPE_2__ tx_msg; int /*<<< orphan*/  tx_ignore_nack_until_eom; int /*<<< orphan*/  ts; TYPE_1__ rx_msg; int /*<<< orphan*/  kthread_waitq; void* work_tx_status; void* work_tx_ts; int /*<<< orphan*/  tx_generated_poll; int /*<<< orphan*/  tx_low_drive_cnt; } ;
typedef  void* ktime_t ;

/* Variables and functions */
#define  ACK_BIT 152 
 int CEC_ST_RX_DATA_POST_SAMPLE ; 
#define  CEC_ST_TX_DATA_BIT_0_HIGH 151 
#define  CEC_ST_TX_DATA_BIT_0_HIGH_LONG 150 
#define  CEC_ST_TX_DATA_BIT_0_HIGH_SHORT 149 
#define  CEC_ST_TX_DATA_BIT_0_LOW 148 
#define  CEC_ST_TX_DATA_BIT_1_HIGH 147 
#define  CEC_ST_TX_DATA_BIT_1_HIGH_LONG 146 
#define  CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPLE 145 
#define  CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPLE_LONG 144 
#define  CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPLE_SHORT 143 
#define  CEC_ST_TX_DATA_BIT_1_HIGH_PRE_SAMPLE 142 
#define  CEC_ST_TX_DATA_BIT_1_HIGH_SHORT 141 
#define  CEC_ST_TX_DATA_BIT_1_LOW 140 
#define  CEC_ST_TX_DATA_BIT_HIGH_CUSTOM 139 
#define  CEC_ST_TX_DATA_BIT_LOW_CUSTOM 138 
 int CEC_ST_TX_LOW_DRIVE ; 
#define  CEC_ST_TX_PULSE_HIGH_CUSTOM 137 
#define  CEC_ST_TX_PULSE_LOW_CUSTOM 136 
#define  CEC_ST_TX_START_BIT_HIGH 135 
#define  CEC_ST_TX_START_BIT_HIGH_CUSTOM 134 
#define  CEC_ST_TX_START_BIT_HIGH_LONG 133 
#define  CEC_ST_TX_START_BIT_HIGH_SHORT 132 
#define  CEC_ST_TX_START_BIT_LOW 131 
#define  CEC_ST_TX_START_BIT_LOW_CUSTOM 130 
#define  CEC_ST_TX_WAIT_FOR_HIGH 129 
 int /*<<< orphan*/  CEC_TIM_DATA_BIT_SAMPLE ; 
 void* CEC_TX_STATUS_ARB_LOST ; 
 void* CEC_TX_STATUS_LOW_DRIVE ; 
 void* CEC_TX_STATUS_NACK ; 
 void* CEC_TX_STATUS_OK ; 
#define  EOM_BIT 128 
 int /*<<< orphan*/  cec_msg_is_broadcast (TYPE_2__*) ; 
 int /*<<< orphan*/  cec_pin_high (struct cec_pin*) ; 
 int /*<<< orphan*/  cec_pin_low (struct cec_pin*) ; 
 int cec_pin_read (struct cec_pin*) ; 
 int /*<<< orphan*/  cec_pin_to_idle (struct cec_pin*) ; 
 int /*<<< orphan*/  ktime_sub_us (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tx_custom_bit (struct cec_pin*) ; 
 int /*<<< orphan*/  tx_early_eom (struct cec_pin*) ; 
 int /*<<< orphan*/  tx_last_bit (struct cec_pin*) ; 
 int /*<<< orphan*/  tx_long_bit (struct cec_pin*) ; 
 int /*<<< orphan*/  tx_long_start (struct cec_pin*) ; 
 int /*<<< orphan*/  tx_low_drive (struct cec_pin*) ; 
 int /*<<< orphan*/  tx_no_eom (struct cec_pin*) ; 
 int /*<<< orphan*/  tx_short_bit (struct cec_pin*) ; 
 int /*<<< orphan*/  tx_short_start (struct cec_pin*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cec_pin_tx_states(struct cec_pin *pin, ktime_t ts)
{
	bool v;
	bool is_ack_bit, ack;

	switch (pin->state) {
	case CEC_ST_TX_WAIT_FOR_HIGH:
		if (cec_pin_read(pin))
			cec_pin_to_idle(pin);
		break;

	case CEC_ST_TX_START_BIT_LOW:
		if (tx_short_start(pin)) {
			/*
			 * Error Injection: send an invalid (too short)
			 * start pulse.
			 */
			pin->state = CEC_ST_TX_START_BIT_HIGH_SHORT;
		} else if (tx_long_start(pin)) {
			/*
			 * Error Injection: send an invalid (too long)
			 * start pulse.
			 */
			pin->state = CEC_ST_TX_START_BIT_HIGH_LONG;
		} else {
			pin->state = CEC_ST_TX_START_BIT_HIGH;
		}
		/* Generate start bit */
		cec_pin_high(pin);
		break;

	case CEC_ST_TX_START_BIT_LOW_CUSTOM:
		pin->state = CEC_ST_TX_START_BIT_HIGH_CUSTOM;
		/* Generate start bit */
		cec_pin_high(pin);
		break;

	case CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPLE:
	case CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPLE_SHORT:
	case CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPLE_LONG:
		if (pin->tx_nacked) {
			cec_pin_to_idle(pin);
			pin->tx_msg.len = 0;
			if (pin->tx_generated_poll)
				break;
			pin->work_tx_ts = ts;
			pin->work_tx_status = CEC_TX_STATUS_NACK;
			wake_up_interruptible(&pin->kthread_waitq);
			break;
		}
		/* fall through */
	case CEC_ST_TX_DATA_BIT_0_HIGH:
	case CEC_ST_TX_DATA_BIT_0_HIGH_SHORT:
	case CEC_ST_TX_DATA_BIT_0_HIGH_LONG:
	case CEC_ST_TX_DATA_BIT_1_HIGH:
	case CEC_ST_TX_DATA_BIT_1_HIGH_SHORT:
	case CEC_ST_TX_DATA_BIT_1_HIGH_LONG:
		/*
		 * If the read value is 1, then all is OK, otherwise we have a
		 * low drive condition.
		 *
		 * Special case: when we generate a poll message due to an
		 * Arbitration Lost error injection, then ignore this since
		 * the pin can actually be low in that case.
		 */
		if (!cec_pin_read(pin) && !pin->tx_generated_poll) {
			/*
			 * It's 0, so someone detected an error and pulled the
			 * line low for 1.5 times the nominal bit period.
			 */
			pin->tx_msg.len = 0;
			pin->state = CEC_ST_TX_WAIT_FOR_HIGH;
			pin->work_tx_ts = ts;
			pin->work_tx_status = CEC_TX_STATUS_LOW_DRIVE;
			pin->tx_low_drive_cnt++;
			wake_up_interruptible(&pin->kthread_waitq);
			break;
		}
		/* fall through */
	case CEC_ST_TX_DATA_BIT_HIGH_CUSTOM:
		if (tx_last_bit(pin)) {
			/* Error Injection: just stop sending after this bit */
			cec_pin_to_idle(pin);
			pin->tx_msg.len = 0;
			if (pin->tx_generated_poll)
				break;
			pin->work_tx_ts = ts;
			pin->work_tx_status = CEC_TX_STATUS_OK;
			wake_up_interruptible(&pin->kthread_waitq);
			break;
		}
		pin->tx_bit++;
		/* fall through */
	case CEC_ST_TX_START_BIT_HIGH:
	case CEC_ST_TX_START_BIT_HIGH_SHORT:
	case CEC_ST_TX_START_BIT_HIGH_LONG:
	case CEC_ST_TX_START_BIT_HIGH_CUSTOM:
		if (tx_low_drive(pin)) {
			/* Error injection: go to low drive */
			cec_pin_low(pin);
			pin->state = CEC_ST_TX_LOW_DRIVE;
			pin->tx_msg.len = 0;
			if (pin->tx_generated_poll)
				break;
			pin->work_tx_ts = ts;
			pin->work_tx_status = CEC_TX_STATUS_LOW_DRIVE;
			pin->tx_low_drive_cnt++;
			wake_up_interruptible(&pin->kthread_waitq);
			break;
		}
		if (pin->tx_bit / 10 >= pin->tx_msg.len + pin->tx_extra_bytes) {
			cec_pin_to_idle(pin);
			pin->tx_msg.len = 0;
			if (pin->tx_generated_poll)
				break;
			pin->work_tx_ts = ts;
			pin->work_tx_status = CEC_TX_STATUS_OK;
			wake_up_interruptible(&pin->kthread_waitq);
			break;
		}

		switch (pin->tx_bit % 10) {
		default: {
			/*
			 * In the CEC_ERROR_INJ_TX_ADD_BYTES case we transmit
			 * extra bytes, so pin->tx_bit / 10 can become >= 16.
			 * Generate bit values for those extra bytes instead
			 * of reading them from the transmit buffer.
			 */
			unsigned int idx = (pin->tx_bit / 10);
			u8 val = idx;

			if (idx < pin->tx_msg.len)
				val = pin->tx_msg.msg[idx];
			v = val & (1 << (7 - (pin->tx_bit % 10)));

			pin->state = v ? CEC_ST_TX_DATA_BIT_1_LOW :
					 CEC_ST_TX_DATA_BIT_0_LOW;
			break;
		}
		case EOM_BIT: {
			unsigned int tot_len = pin->tx_msg.len +
					       pin->tx_extra_bytes;
			unsigned int tx_byte_idx = pin->tx_bit / 10;

			v = !pin->tx_post_eom && tx_byte_idx == tot_len - 1;
			if (tot_len > 1 && tx_byte_idx == tot_len - 2 &&
			    tx_early_eom(pin)) {
				/* Error injection: set EOM one byte early */
				v = true;
				pin->tx_post_eom = true;
			} else if (v && tx_no_eom(pin)) {
				/* Error injection: no EOM */
				v = false;
			}
			pin->state = v ? CEC_ST_TX_DATA_BIT_1_LOW :
					 CEC_ST_TX_DATA_BIT_0_LOW;
			break;
		}
		case ACK_BIT:
			pin->state = CEC_ST_TX_DATA_BIT_1_LOW;
			break;
		}
		if (tx_custom_bit(pin))
			pin->state = CEC_ST_TX_DATA_BIT_LOW_CUSTOM;
		cec_pin_low(pin);
		break;

	case CEC_ST_TX_DATA_BIT_0_LOW:
	case CEC_ST_TX_DATA_BIT_1_LOW:
		v = pin->state == CEC_ST_TX_DATA_BIT_1_LOW;
		is_ack_bit = pin->tx_bit % 10 == ACK_BIT;
		if (v && (pin->tx_bit < 4 || is_ack_bit)) {
			pin->state = CEC_ST_TX_DATA_BIT_1_HIGH_PRE_SAMPLE;
		} else if (!is_ack_bit && tx_short_bit(pin)) {
			/* Error Injection: send an invalid (too short) bit */
			pin->state = v ? CEC_ST_TX_DATA_BIT_1_HIGH_SHORT :
					 CEC_ST_TX_DATA_BIT_0_HIGH_SHORT;
		} else if (!is_ack_bit && tx_long_bit(pin)) {
			/* Error Injection: send an invalid (too long) bit */
			pin->state = v ? CEC_ST_TX_DATA_BIT_1_HIGH_LONG :
					 CEC_ST_TX_DATA_BIT_0_HIGH_LONG;
		} else {
			pin->state = v ? CEC_ST_TX_DATA_BIT_1_HIGH :
					 CEC_ST_TX_DATA_BIT_0_HIGH;
		}
		cec_pin_high(pin);
		break;

	case CEC_ST_TX_DATA_BIT_LOW_CUSTOM:
		pin->state = CEC_ST_TX_DATA_BIT_HIGH_CUSTOM;
		cec_pin_high(pin);
		break;

	case CEC_ST_TX_DATA_BIT_1_HIGH_PRE_SAMPLE:
		/* Read the CEC value at the sample time */
		v = cec_pin_read(pin);
		is_ack_bit = pin->tx_bit % 10 == ACK_BIT;
		/*
		 * If v == 0 and we're within the first 4 bits
		 * of the initiator, then someone else started
		 * transmitting and we lost the arbitration
		 * (i.e. the logical address of the other
		 * transmitter has more leading 0 bits in the
		 * initiator).
		 */
		if (!v && !is_ack_bit && !pin->tx_generated_poll) {
			pin->tx_msg.len = 0;
			pin->work_tx_ts = ts;
			pin->work_tx_status = CEC_TX_STATUS_ARB_LOST;
			wake_up_interruptible(&pin->kthread_waitq);
			pin->rx_bit = pin->tx_bit;
			pin->tx_bit = 0;
			memset(pin->rx_msg.msg, 0, sizeof(pin->rx_msg.msg));
			pin->rx_msg.msg[0] = pin->tx_msg.msg[0];
			pin->rx_msg.msg[0] &= (0xff << (8 - pin->rx_bit));
			pin->rx_msg.len = 0;
			pin->ts = ktime_sub_us(ts, CEC_TIM_DATA_BIT_SAMPLE);
			pin->state = CEC_ST_RX_DATA_POST_SAMPLE;
			pin->rx_bit++;
			break;
		}
		pin->state = CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPLE;
		if (!is_ack_bit && tx_short_bit(pin)) {
			/* Error Injection: send an invalid (too short) bit */
			pin->state = CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPLE_SHORT;
		} else if (!is_ack_bit && tx_long_bit(pin)) {
			/* Error Injection: send an invalid (too long) bit */
			pin->state = CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPLE_LONG;
		}
		if (!is_ack_bit)
			break;
		/* Was the message ACKed? */
		ack = cec_msg_is_broadcast(&pin->tx_msg) ? v : !v;
		if (!ack && (!pin->tx_ignore_nack_until_eom ||
		    pin->tx_bit / 10 == pin->tx_msg.len - 1) &&
		    !pin->tx_post_eom) {
			/*
			 * Note: the CEC spec is ambiguous regarding
			 * what action to take when a NACK appears
			 * before the last byte of the payload was
			 * transmitted: either stop transmitting
			 * immediately, or wait until the last byte
			 * was transmitted.
			 *
			 * Most CEC implementations appear to stop
			 * immediately, and that's what we do here
			 * as well.
			 */
			pin->tx_nacked = true;
		}
		break;

	case CEC_ST_TX_PULSE_LOW_CUSTOM:
		cec_pin_high(pin);
		pin->state = CEC_ST_TX_PULSE_HIGH_CUSTOM;
		break;

	case CEC_ST_TX_PULSE_HIGH_CUSTOM:
		cec_pin_to_idle(pin);
		break;

	default:
		break;
	}
}