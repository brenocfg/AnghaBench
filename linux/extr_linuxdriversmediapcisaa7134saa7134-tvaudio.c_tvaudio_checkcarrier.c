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
struct saa7134_dev {TYPE_1__* tvnorm; } ;
struct mainscan {int std; int carr; int /*<<< orphan*/  name; } ;
typedef  int __s32 ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int SAA7134_LEVEL_READOUT1 ; 
 int /*<<< orphan*/  SCAN_SAMPLE_DELAY ; 
 int /*<<< orphan*/  audio_dbg (int,char*,int,...) ; 
 int audio_debug ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int saa_readl (int) ; 
 int /*<<< orphan*/  tvaudio_setcarrier (struct saa7134_dev*,int,int) ; 
 scalar_t__ tvaudio_sleep (struct saa7134_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tvaudio_checkcarrier(struct saa7134_dev *dev, struct mainscan *scan)
{
	__s32 left,right,value;

	if (!(dev->tvnorm->id & scan->std)) {
		value = 0;
		audio_dbg(1, "skipping %d.%03d MHz [%4s]\n",
			  scan->carr / 1000, scan->carr % 1000, scan->name);
		return 0;
	}

	if (audio_debug > 1) {
		int i;
		audio_dbg(1, "debug %d:", scan->carr);
		for (i = -150; i <= 150; i += 30) {
			tvaudio_setcarrier(dev,scan->carr+i,scan->carr+i);
			saa_readl(SAA7134_LEVEL_READOUT1 >> 2);
			if (tvaudio_sleep(dev,SCAN_SAMPLE_DELAY))
				return -1;
			value = saa_readl(SAA7134_LEVEL_READOUT1 >> 2);
			if (0 == i)
				pr_cont("  #  %6d  # ", value >> 16);
			else
				pr_cont(" %6d", value >> 16);
		}
		pr_cont("\n");
	}

	tvaudio_setcarrier(dev,scan->carr-90,scan->carr-90);
	saa_readl(SAA7134_LEVEL_READOUT1 >> 2);
	if (tvaudio_sleep(dev,SCAN_SAMPLE_DELAY))
		return -1;
	left = saa_readl(SAA7134_LEVEL_READOUT1 >> 2);

	tvaudio_setcarrier(dev,scan->carr+90,scan->carr+90);
	saa_readl(SAA7134_LEVEL_READOUT1 >> 2);
	if (tvaudio_sleep(dev,SCAN_SAMPLE_DELAY))
		return -1;
	right = saa_readl(SAA7134_LEVEL_READOUT1 >> 2);

	left >>= 16;
	right >>= 16;
	value = left > right ? left - right : right - left;
	audio_dbg(1, "scanning %d.%03d MHz [%4s] =>  dc is %5d [%d/%d]\n",
		  scan->carr / 1000, scan->carr % 1000,
		  scan->name, value, left, right);
	return value;
}