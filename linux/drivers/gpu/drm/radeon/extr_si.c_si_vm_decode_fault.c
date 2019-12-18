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
struct radeon_device {scalar_t__ family; } ;

/* Variables and functions */
 scalar_t__ CHIP_TAHITI ; 
 int FAULT_VMID_MASK ; 
 int FAULT_VMID_SHIFT ; 
 int MEMORY_CLIENT_ID_MASK ; 
 int MEMORY_CLIENT_ID_SHIFT ; 
 int MEMORY_CLIENT_RW_MASK ; 
 int PROTECTIONS_MASK ; 
 int PROTECTIONS_SHIFT ; 
 int /*<<< orphan*/  printk (char*,int,int,int,char*,char*,int) ; 

__attribute__((used)) static void si_vm_decode_fault(struct radeon_device *rdev,
			       u32 status, u32 addr)
{
	u32 mc_id = (status & MEMORY_CLIENT_ID_MASK) >> MEMORY_CLIENT_ID_SHIFT;
	u32 vmid = (status & FAULT_VMID_MASK) >> FAULT_VMID_SHIFT;
	u32 protections = (status & PROTECTIONS_MASK) >> PROTECTIONS_SHIFT;
	char *block;

	if (rdev->family == CHIP_TAHITI) {
		switch (mc_id) {
		case 160:
		case 144:
		case 96:
		case 80:
		case 224:
		case 208:
		case 32:
		case 16:
			block = "CB";
			break;
		case 161:
		case 145:
		case 97:
		case 81:
		case 225:
		case 209:
		case 33:
		case 17:
			block = "CB_FMASK";
			break;
		case 162:
		case 146:
		case 98:
		case 82:
		case 226:
		case 210:
		case 34:
		case 18:
			block = "CB_CMASK";
			break;
		case 163:
		case 147:
		case 99:
		case 83:
		case 227:
		case 211:
		case 35:
		case 19:
			block = "CB_IMMED";
			break;
		case 164:
		case 148:
		case 100:
		case 84:
		case 228:
		case 212:
		case 36:
		case 20:
			block = "DB";
			break;
		case 165:
		case 149:
		case 101:
		case 85:
		case 229:
		case 213:
		case 37:
		case 21:
			block = "DB_HTILE";
			break;
		case 167:
		case 151:
		case 103:
		case 87:
		case 231:
		case 215:
		case 39:
		case 23:
			block = "DB_STEN";
			break;
		case 72:
		case 68:
		case 64:
		case 8:
		case 4:
		case 0:
		case 136:
		case 132:
		case 128:
		case 200:
		case 196:
		case 192:
			block = "TC";
			break;
		case 112:
		case 48:
			block = "CP";
			break;
		case 49:
		case 177:
		case 50:
		case 178:
			block = "SH";
			break;
		case 53:
		case 190:
			block = "VGT";
			break;
		case 117:
			block = "IH";
			break;
		case 51:
		case 115:
			block = "RLC";
			break;
		case 119:
		case 183:
			block = "DMA0";
			break;
		case 61:
			block = "DMA1";
			break;
		case 248:
		case 120:
			block = "HDP";
			break;
		default:
			block = "unknown";
			break;
		}
	} else {
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
		case 72:
		case 68:
		case 8:
		case 4:
		case 136:
		case 132:
		case 200:
		case 196:
			block = "TC";
			break;
		case 112:
		case 48:
			block = "CP";
			break;
		case 49:
		case 177:
		case 50:
		case 178:
			block = "SH";
			break;
		case 53:
			block = "VGT";
			break;
		case 117:
			block = "IH";
			break;
		case 51:
		case 115:
			block = "RLC";
			break;
		case 119:
		case 183:
			block = "DMA0";
			break;
		case 61:
			block = "DMA1";
			break;
		case 248:
		case 120:
			block = "HDP";
			break;
		default:
			block = "unknown";
			break;
		}
	}

	printk("VM fault (0x%02x, vmid %d) at page %u, %s from %s (%d)\n",
	       protections, vmid, addr,
	       (status & MEMORY_CLIENT_RW_MASK) ? "write" : "read",
	       block, mc_id);
}