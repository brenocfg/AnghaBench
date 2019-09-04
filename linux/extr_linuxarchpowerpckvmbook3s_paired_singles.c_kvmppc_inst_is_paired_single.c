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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int hflags; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int BOOK3S_HFLAG_PAIRED_SINGLE ; 
#define  OP_31_LFDUX 216 
#define  OP_31_LFDX 215 
#define  OP_31_LFSUX 214 
#define  OP_31_LFSX 213 
#define  OP_31_STFIWX 212 
#define  OP_31_STFSUX 211 
#define  OP_31_STFSX 210 
#define  OP_31_STFUX 209 
#define  OP_31_STFX 208 
#define  OP_4A_PS_ADD 207 
#define  OP_4A_PS_DIV 206 
#define  OP_4A_PS_MADD 205 
#define  OP_4A_PS_MADDS0 204 
#define  OP_4A_PS_MADDS1 203 
#define  OP_4A_PS_MSUB 202 
#define  OP_4A_PS_MUL 201 
#define  OP_4A_PS_MULS0 200 
#define  OP_4A_PS_MULS1 199 
#define  OP_4A_PS_NMADD 198 
#define  OP_4A_PS_NMSUB 197 
#define  OP_4A_PS_RES 196 
#define  OP_4A_PS_RSQRTE 195 
#define  OP_4A_PS_SEL 194 
#define  OP_4A_PS_SUB 193 
#define  OP_4A_PS_SUM0 192 
#define  OP_4A_PS_SUM1 191 
#define  OP_4XW_PSQ_STUX 190 
#define  OP_4XW_PSQ_STX 189 
#define  OP_4X_PSQ_LUX 188 
#define  OP_4X_PSQ_LX 187 
#define  OP_4X_PS_ABS 186 
#define  OP_4X_PS_CMPO0 185 
#define  OP_4X_PS_CMPO1 184 
#define  OP_4X_PS_CMPU0 183 
#define  OP_4X_PS_CMPU1 182 
#define  OP_4X_PS_MERGE00 181 
#define  OP_4X_PS_MERGE01 180 
#define  OP_4X_PS_MERGE10 179 
#define  OP_4X_PS_MERGE11 178 
#define  OP_4X_PS_MR 177 
#define  OP_4X_PS_NABS 176 
#define  OP_4X_PS_NEG 175 
#define  OP_59_FADDS 174 
#define  OP_59_FDIVS 173 
#define  OP_59_FMADDS 172 
#define  OP_59_FMSUBS 171 
#define  OP_59_FMULS 170 
#define  OP_59_FNMADDS 169 
#define  OP_59_FNMSUBS 168 
#define  OP_59_FRES 167 
#define  OP_59_FRSQRTES 166 
#define  OP_59_FSUBS 165 
#define  OP_63_FABS 164 
#define  OP_63_FADD 163 
#define  OP_63_FCMPO 162 
#define  OP_63_FCMPU 161 
#define  OP_63_FCPSGN 160 
#define  OP_63_FCTIW 159 
#define  OP_63_FCTIWZ 158 
#define  OP_63_FDIV 157 
#define  OP_63_FMADD 156 
#define  OP_63_FMR 155 
#define  OP_63_FMSUB 154 
#define  OP_63_FMUL 153 
#define  OP_63_FNEG 152 
#define  OP_63_FNMADD 151 
#define  OP_63_FNMSUB 150 
#define  OP_63_FRSP 149 
#define  OP_63_FRSQRTE 148 
#define  OP_63_FSEL 147 
#define  OP_63_FSUB 146 
#define  OP_63_MCRFS 145 
#define  OP_63_MFFS 144 
#define  OP_63_MTFSB0 143 
#define  OP_63_MTFSB1 142 
#define  OP_63_MTFSF 141 
#define  OP_63_MTFSFI 140 
#define  OP_LFD 139 
#define  OP_LFDU 138 
#define  OP_LFS 137 
#define  OP_LFSU 136 
#define  OP_PSQ_L 135 
#define  OP_PSQ_LU 134 
#define  OP_PSQ_ST 133 
#define  OP_PSQ_STU 132 
#define  OP_STFD 131 
#define  OP_STFDU 130 
#define  OP_STFS 129 
#define  OP_STFSU 128 
 int get_op (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inst_get_field (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static bool kvmppc_inst_is_paired_single(struct kvm_vcpu *vcpu, u32 inst)
{
	if (!(vcpu->arch.hflags & BOOK3S_HFLAG_PAIRED_SINGLE))
		return false;

	switch (get_op(inst)) {
	case OP_PSQ_L:
	case OP_PSQ_LU:
	case OP_PSQ_ST:
	case OP_PSQ_STU:
	case OP_LFS:
	case OP_LFSU:
	case OP_LFD:
	case OP_LFDU:
	case OP_STFS:
	case OP_STFSU:
	case OP_STFD:
	case OP_STFDU:
		return true;
	case 4:
		/* X form */
		switch (inst_get_field(inst, 21, 30)) {
		case OP_4X_PS_CMPU0:
		case OP_4X_PSQ_LX:
		case OP_4X_PS_CMPO0:
		case OP_4X_PSQ_LUX:
		case OP_4X_PS_NEG:
		case OP_4X_PS_CMPU1:
		case OP_4X_PS_MR:
		case OP_4X_PS_CMPO1:
		case OP_4X_PS_NABS:
		case OP_4X_PS_ABS:
		case OP_4X_PS_MERGE00:
		case OP_4X_PS_MERGE01:
		case OP_4X_PS_MERGE10:
		case OP_4X_PS_MERGE11:
			return true;
		}
		/* XW form */
		switch (inst_get_field(inst, 25, 30)) {
		case OP_4XW_PSQ_STX:
		case OP_4XW_PSQ_STUX:
			return true;
		}
		/* A form */
		switch (inst_get_field(inst, 26, 30)) {
		case OP_4A_PS_SUM1:
		case OP_4A_PS_SUM0:
		case OP_4A_PS_MULS0:
		case OP_4A_PS_MULS1:
		case OP_4A_PS_MADDS0:
		case OP_4A_PS_MADDS1:
		case OP_4A_PS_DIV:
		case OP_4A_PS_SUB:
		case OP_4A_PS_ADD:
		case OP_4A_PS_SEL:
		case OP_4A_PS_RES:
		case OP_4A_PS_MUL:
		case OP_4A_PS_RSQRTE:
		case OP_4A_PS_MSUB:
		case OP_4A_PS_MADD:
		case OP_4A_PS_NMSUB:
		case OP_4A_PS_NMADD:
			return true;
		}
		break;
	case 59:
		switch (inst_get_field(inst, 21, 30)) {
		case OP_59_FADDS:
		case OP_59_FSUBS:
		case OP_59_FDIVS:
		case OP_59_FRES:
		case OP_59_FRSQRTES:
			return true;
		}
		switch (inst_get_field(inst, 26, 30)) {
		case OP_59_FMULS:
		case OP_59_FMSUBS:
		case OP_59_FMADDS:
		case OP_59_FNMSUBS:
		case OP_59_FNMADDS:
			return true;
		}
		break;
	case 63:
		switch (inst_get_field(inst, 21, 30)) {
		case OP_63_MTFSB0:
		case OP_63_MTFSB1:
		case OP_63_MTFSF:
		case OP_63_MTFSFI:
		case OP_63_MCRFS:
		case OP_63_MFFS:
		case OP_63_FCMPU:
		case OP_63_FCMPO:
		case OP_63_FNEG:
		case OP_63_FMR:
		case OP_63_FABS:
		case OP_63_FRSP:
		case OP_63_FDIV:
		case OP_63_FADD:
		case OP_63_FSUB:
		case OP_63_FCTIW:
		case OP_63_FCTIWZ:
		case OP_63_FRSQRTE:
		case OP_63_FCPSGN:
			return true;
		}
		switch (inst_get_field(inst, 26, 30)) {
		case OP_63_FMUL:
		case OP_63_FSEL:
		case OP_63_FMSUB:
		case OP_63_FMADD:
		case OP_63_FNMSUB:
		case OP_63_FNMADD:
			return true;
		}
		break;
	case 31:
		switch (inst_get_field(inst, 21, 30)) {
		case OP_31_LFSX:
		case OP_31_LFSUX:
		case OP_31_LFDX:
		case OP_31_LFDUX:
		case OP_31_STFSX:
		case OP_31_STFSUX:
		case OP_31_STFX:
		case OP_31_STFUX:
		case OP_31_STFIWX:
			return true;
		}
		break;
	}

	return false;
}