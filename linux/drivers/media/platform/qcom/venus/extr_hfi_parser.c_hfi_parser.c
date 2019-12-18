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
typedef  int u32 ;
struct venus_inst {int dummy; } ;
struct venus_core {int dummy; } ;

/* Variables and functions */
 int HFI_ERR_NONE ; 
 int HFI_ERR_SYS_INSUFFICIENT_RESOURCES ; 
#define  HFI_PROPERTY_PARAM_BUFFER_ALLOC_MODE_SUPPORTED 134 
#define  HFI_PROPERTY_PARAM_CAPABILITY_SUPPORTED 133 
#define  HFI_PROPERTY_PARAM_CODEC_MASK_SUPPORTED 132 
#define  HFI_PROPERTY_PARAM_CODEC_SUPPORTED 131 
#define  HFI_PROPERTY_PARAM_MAX_SESSIONS_SUPPORTED 130 
#define  HFI_PROPERTY_PARAM_PROFILE_LEVEL_SUPPORTED 129 
#define  HFI_PROPERTY_PARAM_UNCOMPRESSED_FORMAT_SUPPORTED 128 
 int /*<<< orphan*/  init_codecs (struct venus_core*) ; 
 int /*<<< orphan*/  parse_alloc_mode (struct venus_core*,int,int,int*) ; 
 int /*<<< orphan*/  parse_caps (struct venus_core*,int,int,int*) ; 
 int /*<<< orphan*/  parse_codecs (struct venus_core*,int*) ; 
 int /*<<< orphan*/  parse_codecs_mask (int*,int*,int*) ; 
 int /*<<< orphan*/  parse_max_sessions (struct venus_core*,int*) ; 
 int /*<<< orphan*/  parse_profile_level (struct venus_core*,int,int,int*) ; 
 int /*<<< orphan*/  parse_raw_formats (struct venus_core*,int,int,int*) ; 
 int /*<<< orphan*/  parser_fini (struct venus_inst*,int,int) ; 
 int /*<<< orphan*/  parser_init (struct venus_inst*,int*,int*) ; 

u32 hfi_parser(struct venus_core *core, struct venus_inst *inst, void *buf,
	       u32 size)
{
	unsigned int words_count = size >> 2;
	u32 *word = buf, *data, codecs = 0, domain = 0;

	if (size % 4)
		return HFI_ERR_SYS_INSUFFICIENT_RESOURCES;

	parser_init(inst, &codecs, &domain);

	while (words_count) {
		data = word + 1;

		switch (*word) {
		case HFI_PROPERTY_PARAM_CODEC_SUPPORTED:
			parse_codecs(core, data);
			init_codecs(core);
			break;
		case HFI_PROPERTY_PARAM_MAX_SESSIONS_SUPPORTED:
			parse_max_sessions(core, data);
			break;
		case HFI_PROPERTY_PARAM_CODEC_MASK_SUPPORTED:
			parse_codecs_mask(&codecs, &domain, data);
			break;
		case HFI_PROPERTY_PARAM_UNCOMPRESSED_FORMAT_SUPPORTED:
			parse_raw_formats(core, codecs, domain, data);
			break;
		case HFI_PROPERTY_PARAM_CAPABILITY_SUPPORTED:
			parse_caps(core, codecs, domain, data);
			break;
		case HFI_PROPERTY_PARAM_PROFILE_LEVEL_SUPPORTED:
			parse_profile_level(core, codecs, domain, data);
			break;
		case HFI_PROPERTY_PARAM_BUFFER_ALLOC_MODE_SUPPORTED:
			parse_alloc_mode(core, codecs, domain, data);
			break;
		default:
			break;
		}

		word++;
		words_count--;
	}

	parser_fini(inst, codecs, domain);

	return HFI_ERR_NONE;
}