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
typedef  int /*<<< orphan*/  u32 ;
struct tango_nfc {int freq_kHz; } ;
struct tango_chip {void* timing2; void* timing1; } ;
struct nand_sdr_timings {scalar_t__ tRHZ_max; scalar_t__ tREH_min; scalar_t__ tRC_min; scalar_t__ tREA_max; scalar_t__ tWP_min; scalar_t__ tWC_min; scalar_t__ tWB_max; scalar_t__ tCEA_max; } ;
struct nand_data_interface {int dummy; } ;
struct nand_chip {int /*<<< orphan*/  controller; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nand_sdr_timings const*) ; 
 int NAND_DATA_IFACE_CHECK_ONLY ; 
 int PTR_ERR (struct nand_sdr_timings const*) ; 
 void* TIMING (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nand_sdr_timings* nand_get_sdr_timings (struct nand_data_interface const*) ; 
 struct tango_chip* to_tango_chip (struct nand_chip*) ; 
 struct tango_nfc* to_tango_nfc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_ticks (int,scalar_t__) ; 

__attribute__((used)) static int tango_set_timings(struct nand_chip *chip, int csline,
			     const struct nand_data_interface *conf)
{
	const struct nand_sdr_timings *sdr = nand_get_sdr_timings(conf);
	struct tango_nfc *nfc = to_tango_nfc(chip->controller);
	struct tango_chip *tchip = to_tango_chip(chip);
	u32 Trdy, Textw, Twc, Twpw, Tacc, Thold, Trpw, Textr;
	int kHz = nfc->freq_kHz;

	if (IS_ERR(sdr))
		return PTR_ERR(sdr);

	if (csline == NAND_DATA_IFACE_CHECK_ONLY)
		return 0;

	Trdy = to_ticks(kHz, sdr->tCEA_max - sdr->tREA_max);
	Textw = to_ticks(kHz, sdr->tWB_max);
	Twc = to_ticks(kHz, sdr->tWC_min);
	Twpw = to_ticks(kHz, sdr->tWC_min - sdr->tWP_min);

	Tacc = to_ticks(kHz, sdr->tREA_max);
	Thold = to_ticks(kHz, sdr->tREH_min);
	Trpw = to_ticks(kHz, sdr->tRC_min - sdr->tREH_min);
	Textr = to_ticks(kHz, sdr->tRHZ_max);

	tchip->timing1 = TIMING(Trdy, Textw, Twc, Twpw);
	tchip->timing2 = TIMING(Tacc, Thold, Trpw, Textr);

	return 0;
}