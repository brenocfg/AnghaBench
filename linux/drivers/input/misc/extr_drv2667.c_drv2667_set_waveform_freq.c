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
struct drv2667_data {int frequency; unsigned int page; TYPE_1__* client; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV2667_PAGE ; 
 unsigned int DRV2667_PAGE_0 ; 
 int /*<<< orphan*/  DRV2667_RAM_FREQ ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int drv2667_set_waveform_freq(struct drv2667_data *haptics)
{
	unsigned int read_buf;
	int freq;
	int error;

	/* Per the data sheet:
	 * Sinusoid Frequency (Hz) = 7.8125 x Frequency
	 */
	freq = (haptics->frequency * 1000) / 78125;
	if (freq <= 0) {
		dev_err(&haptics->client->dev,
			"ERROR: Frequency calculated to %i\n", freq);
		return -EINVAL;
	}

	error = regmap_read(haptics->regmap, DRV2667_PAGE, &read_buf);
	if (error) {
		dev_err(&haptics->client->dev,
			"Failed to read the page number: %d\n", error);
		return -EIO;
	}

	if (read_buf == DRV2667_PAGE_0 ||
		haptics->page != read_buf) {
		error = regmap_write(haptics->regmap,
				DRV2667_PAGE, haptics->page);
		if (error) {
			dev_err(&haptics->client->dev,
				"Failed to set the page: %d\n", error);
			return -EIO;
		}
	}

	error = regmap_write(haptics->regmap, DRV2667_RAM_FREQ,	freq);
	if (error)
		dev_err(&haptics->client->dev,
				"Failed to set the frequency: %d\n", error);

	/* Reset back to original page */
	if (read_buf == DRV2667_PAGE_0 ||
		haptics->page != read_buf) {
		error = regmap_write(haptics->regmap, DRV2667_PAGE, read_buf);
		if (error) {
			dev_err(&haptics->client->dev,
				"Failed to set the page: %d\n", error);
			return -EIO;
		}
	}

	return error;
}