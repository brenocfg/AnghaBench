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
typedef  long u32 ;
struct awg_code_generation_params {size_t instruction_offset; long* ram_code; } ;
typedef  enum opcode { ____Placeholder_opcode } opcode ;

/* Variables and functions */
 long AWG_MAX_ARG ; 
 size_t AWG_MAX_INST ; 
 int AWG_OPCODE_OFFSET ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
#define  HOLD 136 
#define  JUMP 135 
#define  REPEAT 134 
#define  REPLAY 133 
#define  RPLSET 132 
#define  RPTSET 131 
#define  SET 130 
#define  SKIP 129 
#define  STOP 128 

__attribute__((used)) static int awg_generate_instr(enum opcode opcode,
			      long int arg,
			      long int mux_sel,
			      long int data_en,
			      struct awg_code_generation_params *fwparams)
{
	u32 instruction = 0;
	u32 mux = (mux_sel << 8) & 0x1ff;
	u32 data_enable = (data_en << 9) & 0x2ff;
	long int arg_tmp = arg;

	/* skip, repeat and replay arg should not exceed 1023.
	 * If user wants to exceed this value, the instruction should be
	 * duplicate and arg should be adjust for each duplicated instruction.
	 *
	 * mux_sel is used in case of SAV/EAV synchronization.
	 */

	while (arg_tmp > 0) {
		arg = arg_tmp;
		if (fwparams->instruction_offset >= AWG_MAX_INST) {
			DRM_ERROR("too many number of instructions\n");
			return -EINVAL;
		}

		switch (opcode) {
		case SKIP:
			/* leave 'arg' + 1 pixel elapsing without changing
			 * output bus */
			arg--; /* pixel adjustment */
			arg_tmp--;

			if (arg < 0) {
				/* SKIP instruction not needed */
				return 0;
			}

			if (arg == 0) {
				/* SKIP 0 not permitted but we want to skip 1
				 * pixel. So we transform SKIP into SET
				 * instruction */
				opcode = SET;
				break;
			}

			mux = 0;
			data_enable = 0;
			arg &= AWG_MAX_ARG;
			break;
		case REPEAT:
		case REPLAY:
			if (arg == 0) {
				/* REPEAT or REPLAY instruction not needed */
				return 0;
			}

			mux = 0;
			data_enable = 0;
			arg &= AWG_MAX_ARG;
			break;
		case JUMP:
			mux = 0;
			data_enable = 0;
			arg |= 0x40; /* for jump instruction 7th bit is 1 */
			arg &= AWG_MAX_ARG;
			break;
		case STOP:
			arg = 0;
			break;
		case SET:
		case RPTSET:
		case RPLSET:
		case HOLD:
			arg &= (0x0ff);
			break;
		default:
			DRM_ERROR("instruction %d does not exist\n", opcode);
			return -EINVAL;
		}

		arg_tmp = arg_tmp - arg;

		arg = ((arg + mux) + data_enable);

		instruction = ((opcode) << AWG_OPCODE_OFFSET) | arg;
		fwparams->ram_code[fwparams->instruction_offset] =
			instruction & (0x3fff);
		fwparams->instruction_offset++;
	}
	return 0;
}