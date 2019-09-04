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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct xc4000_priv {scalar_t__ video_standard; } ;

/* Variables and functions */
 scalar_t__ XC4000_DTV6 ; 
 int /*<<< orphan*/  dprintk (int,char*,int,...) ; 
 int /*<<< orphan*/  xc_get_adc_envelope (struct xc4000_priv*,int*) ; 
 int /*<<< orphan*/  xc_get_frame_lines (struct xc4000_priv*,int*) ; 
 int /*<<< orphan*/  xc_get_frequency_error (struct xc4000_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xc_get_hsync_freq (struct xc4000_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xc_get_lock_status (struct xc4000_priv*,int*) ; 
 int /*<<< orphan*/  xc_get_noise_level (struct xc4000_priv*,int*) ; 
 int /*<<< orphan*/  xc_get_quality (struct xc4000_priv*,int*) ; 
 int /*<<< orphan*/  xc_get_signal_level (struct xc4000_priv*,int*) ; 
 int /*<<< orphan*/  xc_get_version (struct xc4000_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xc_debug_dump(struct xc4000_priv *priv)
{
	u16	adc_envelope;
	u32	freq_error_hz = 0;
	u16	lock_status;
	u32	hsync_freq_hz = 0;
	u16	frame_lines;
	u16	quality;
	u16	signal = 0;
	u16	noise = 0;
	u8	hw_majorversion = 0, hw_minorversion = 0;
	u8	fw_majorversion = 0, fw_minorversion = 0;

	xc_get_adc_envelope(priv, &adc_envelope);
	dprintk(1, "*** ADC envelope (0-1023) = %d\n", adc_envelope);

	xc_get_frequency_error(priv, &freq_error_hz);
	dprintk(1, "*** Frequency error = %d Hz\n", freq_error_hz);

	xc_get_lock_status(priv, &lock_status);
	dprintk(1, "*** Lock status (0-Wait, 1-Locked, 2-No-signal) = %d\n",
		lock_status);

	xc_get_version(priv, &hw_majorversion, &hw_minorversion,
		       &fw_majorversion, &fw_minorversion);
	dprintk(1, "*** HW: V%02x.%02x, FW: V%02x.%02x\n",
		hw_majorversion, hw_minorversion,
		fw_majorversion, fw_minorversion);

	if (priv->video_standard < XC4000_DTV6) {
		xc_get_hsync_freq(priv, &hsync_freq_hz);
		dprintk(1, "*** Horizontal sync frequency = %d Hz\n",
			hsync_freq_hz);

		xc_get_frame_lines(priv, &frame_lines);
		dprintk(1, "*** Frame lines = %d\n", frame_lines);
	}

	xc_get_quality(priv, &quality);
	dprintk(1, "*** Quality (0:<8dB, 7:>56dB) = %d\n", quality);

	xc_get_signal_level(priv, &signal);
	dprintk(1, "*** Signal level = -%ddB (%d)\n", signal >> 8, signal);

	xc_get_noise_level(priv, &noise);
	dprintk(1, "*** Noise level = %ddB (%d)\n", noise >> 8, noise);
}