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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int FAULT_VMID_MASK ; 
 int FAULT_VMID_SHIFT ; 
 int MEMORY_CLIENT_ID_MASK ; 
 int MEMORY_CLIENT_ID_SHIFT ; 
 int MEMORY_CLIENT_RW_MASK ; 
 int PROTECTIONS_MASK ; 
 int PROTECTIONS_SHIFT ; 
 int /*<<< orphan*/  printk (char*,int,int,int,char*,char*,int) ; 

void cayman_vm_decode_fault(struct radeon_device *rdev,
			    u32 status, u32 addr)
{
	u32 mc_id = (status & MEMORY_CLIENT_ID_MASK) >> MEMORY_CLIENT_ID_SHIFT;
	u32 vmid = (status & FAULT_VMID_MASK) >> FAULT_VMID_SHIFT;
	u32 protections = (status & PROTECTIONS_MASK) >> PROTECTIONS_SHIFT;
	char *block;

	switch (mc_id) {
	case 32:
	case 16:
	case 96:
	case 80:
	case 160:
	case 144:
	case 224:
	case 208:
		block = "CB";
		break;
	case 33:
	case 17:
	case 97:
	case 81:
	case 161:
	case 145:
	case 225:
	case 209:
		block = "CB_FMASK";
		break;
	case 34:
	case 18:
	case 98:
	case 82:
	case 162:
	case 146:
	case 226:
	case 210:
		block = "CB_CMASK";
		break;
	case 35:
	case 19:
	case 99:
	case 83:
	case 163:
	case 147:
	case 227:
	case 211:
		block = "CB_IMMED";
		break;
	case 36:
	case 20:
	case 100:
	case 84:
	case 164:
	case 148:
	case 228:
	case 212:
		block = "DB";
		break;
	case 37:
	case 21:
	case 101:
	case 85:
	case 165:
	case 149:
	case 229:
	case 213:
		block = "DB_HTILE";
		break;
	case 38:
	case 22:
	case 102:
	case 86:
	case 166:
	case 150:
	case 230:
	case 214:
		block = "SX";
		break;
	case 39:
	case 23:
	case 103:
	case 87:
	case 167:
	case 151:
	case 231:
	case 215:
		block = "DB_STEN";
		break;
	case 40:
	case 24:
	case 104:
	case 88:
	case 232:
	case 216:
	case 168:
	case 152:
		block = "TC_TFETCH";
		break;
	case 41:
	case 25:
	case 105:
	case 89:
	case 233:
	case 217:
	case 169:
	case 153:
		block = "TC_VFETCH";
		break;
	case 42:
	case 26:
	case 106:
	case 90:
	case 234:
	case 218:
	case 170:
	case 154:
		block = "VC";
		break;
	case 112:
		block = "CP";
		break;
	case 113:
	case 114:
		block = "SH";
		break;
	case 115:
		block = "VGT";
		break;
	case 178:
		block = "IH";
		break;
	case 51:
		block = "RLC";
		break;
	case 55:
		block = "DMA";
		break;
	case 56:
		block = "HDP";
		break;
	default:
		block = "unknown";
		break;
	}

	printk("VM fault (0x%02x, vmid %d) at page %u, %s from %s (%d)\n",
	       protections, vmid, addr,
	       (status & MEMORY_CLIENT_RW_MASK) ? "write" : "read",
	       block, mc_id);
}