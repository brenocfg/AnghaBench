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
typedef  int u_char ;
struct synth_settings {int serial_number; int* rom_version; int /*<<< orphan*/  eob; int /*<<< orphan*/  reverb; int /*<<< orphan*/  articulation; int /*<<< orphan*/  free_ram; int /*<<< orphan*/  ext_dict_status; int /*<<< orphan*/  ext_dict_loaded; int /*<<< orphan*/  expression; int /*<<< orphan*/  tone; int /*<<< orphan*/  volume; int /*<<< orphan*/  speed; int /*<<< orphan*/  pitch; int /*<<< orphan*/  formant_freq; int /*<<< orphan*/  punc_level; int /*<<< orphan*/  mode; } ;
struct spk_synth {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  synth_immediate (struct spk_synth*,char*) ; 
 char synth_read_tts () ; 

__attribute__((used)) static struct synth_settings *synth_interrogate(struct spk_synth *synth)
{
	u_char *t;
	static char buf[sizeof(struct synth_settings) + 1];
	int total, i;
	static struct synth_settings status;

	synth_immediate(synth, "\x18\x01?");
	for (total = 0, i = 0; i < 50; i++) {
		buf[total] = synth_read_tts();
		if (total > 2 && buf[total] == 0x7f)
			break;
		if (total < sizeof(struct synth_settings))
			total++;
	}
	t = buf;
	/* serial number is little endian */
	status.serial_number = t[0] + t[1] * 256;
	t += 2;
	for (i = 0; *t != '\r'; t++) {
		status.rom_version[i] = *t;
		if (i < sizeof(status.rom_version) - 1)
			i++;
	}
	status.rom_version[i] = 0;
	t++;
	status.mode = *t++;
	status.punc_level = *t++;
	status.formant_freq = *t++;
	status.pitch = *t++;
	status.speed = *t++;
	status.volume = *t++;
	status.tone = *t++;
	status.expression = *t++;
	status.ext_dict_loaded = *t++;
	status.ext_dict_status = *t++;
	status.free_ram = *t++;
	status.articulation = *t++;
	status.reverb = *t++;
	status.eob = *t++;
	return &status;
}