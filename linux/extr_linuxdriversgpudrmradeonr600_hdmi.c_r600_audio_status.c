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
typedef  int uint32_t ;
struct radeon_device {int /*<<< orphan*/  dev; } ;
struct r600_audio_pin {int channels; int bits_per_sample; int rate; int status_bits; int category_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  R600_AUDIO_RATE_BPS_CHANNEL ; 
 int /*<<< orphan*/  R600_AUDIO_STATUS_BITS ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static struct r600_audio_pin r600_audio_status(struct radeon_device *rdev)
{
	struct r600_audio_pin status = {};
	uint32_t value;

	value = RREG32(R600_AUDIO_RATE_BPS_CHANNEL);

	/* number of channels */
	status.channels = (value & 0x7) + 1;

	/* bits per sample */
	switch ((value & 0xF0) >> 4) {
	case 0x0:
		status.bits_per_sample = 8;
		break;
	case 0x1:
		status.bits_per_sample = 16;
		break;
	case 0x2:
		status.bits_per_sample = 20;
		break;
	case 0x3:
		status.bits_per_sample = 24;
		break;
	case 0x4:
		status.bits_per_sample = 32;
		break;
	default:
		dev_err(rdev->dev, "Unknown bits per sample 0x%x, using 16\n",
			(int)value);
		status.bits_per_sample = 16;
	}

	/* current sampling rate in HZ */
	if (value & 0x4000)
		status.rate = 44100;
	else
		status.rate = 48000;
	status.rate *= ((value >> 11) & 0x7) + 1;
	status.rate /= ((value >> 8) & 0x7) + 1;

	value = RREG32(R600_AUDIO_STATUS_BITS);

	/* iec 60958 status bits */
	status.status_bits = value & 0xff;

	/* iec 60958 category code */
	status.category_code = (value >> 8) & 0xff;

	return status;
}