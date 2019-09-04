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

/* Variables and functions */
 unsigned long AB ; 
#define  EFDABS 180 
#define  EFDADD 179 
#define  EFDCFS 178 
#define  EFDCMPEQ 177 
#define  EFDCMPGT 176 
#define  EFDCMPLT 175 
#define  EFDCTSF 174 
#define  EFDCTSI 173 
#define  EFDCTSIDZ 172 
#define  EFDCTSIZ 171 
#define  EFDCTUF 170 
#define  EFDCTUI 169 
#define  EFDCTUIDZ 168 
#define  EFDCTUIZ 167 
#define  EFDDIV 166 
#define  EFDMUL 165 
#define  EFDNABS 164 
#define  EFDNEG 163 
#define  EFDSUB 162 
#define  EFSABS 161 
#define  EFSADD 160 
#define  EFSCFD 159 
#define  EFSCFSI 158 
#define  EFSCMPEQ 157 
#define  EFSCMPGT 156 
#define  EFSCMPLT 155 
#define  EFSCTSF 154 
#define  EFSCTSI 153 
#define  EFSCTSIZ 152 
#define  EFSCTUF 151 
#define  EFSCTUI 150 
#define  EFSCTUIZ 149 
#define  EFSDIV 148 
#define  EFSMUL 147 
#define  EFSNABS 146 
#define  EFSNEG 145 
#define  EFSSUB 144 
#define  EVFSABS 143 
#define  EVFSADD 142 
#define  EVFSCMPEQ 141 
#define  EVFSCMPGT 140 
#define  EVFSCMPLT 139 
#define  EVFSCTSF 138 
#define  EVFSCTSI 137 
#define  EVFSCTSIZ 136 
#define  EVFSCTUF 135 
#define  EVFSCTUI 134 
#define  EVFSCTUIZ 133 
#define  EVFSDIV 132 
#define  EVFSMUL 131 
#define  EVFSNABS 130 
#define  EVFSNEG 129 
#define  EVFSSUB 128 
 unsigned long NOTYPE ; 
 unsigned long XA ; 
 unsigned long XB ; 
 unsigned long XCR ; 

__attribute__((used)) static unsigned long insn_type(unsigned long speinsn)
{
	unsigned long ret = NOTYPE;

	switch (speinsn & 0x7ff) {
	case EFSABS:	ret = XA;	break;
	case EFSADD:	ret = AB;	break;
	case EFSCFD:	ret = XB;	break;
	case EFSCMPEQ:	ret = XCR;	break;
	case EFSCMPGT:	ret = XCR;	break;
	case EFSCMPLT:	ret = XCR;	break;
	case EFSCTSF:	ret = XB;	break;
	case EFSCTSI:	ret = XB;	break;
	case EFSCTSIZ:	ret = XB;	break;
	case EFSCTUF:	ret = XB;	break;
	case EFSCTUI:	ret = XB;	break;
	case EFSCTUIZ:	ret = XB;	break;
	case EFSDIV:	ret = AB;	break;
	case EFSMUL:	ret = AB;	break;
	case EFSNABS:	ret = XA;	break;
	case EFSNEG:	ret = XA;	break;
	case EFSSUB:	ret = AB;	break;
	case EFSCFSI:	ret = XB;	break;

	case EVFSABS:	ret = XA;	break;
	case EVFSADD:	ret = AB;	break;
	case EVFSCMPEQ:	ret = XCR;	break;
	case EVFSCMPGT:	ret = XCR;	break;
	case EVFSCMPLT:	ret = XCR;	break;
	case EVFSCTSF:	ret = XB;	break;
	case EVFSCTSI:	ret = XB;	break;
	case EVFSCTSIZ:	ret = XB;	break;
	case EVFSCTUF:	ret = XB;	break;
	case EVFSCTUI:	ret = XB;	break;
	case EVFSCTUIZ:	ret = XB;	break;
	case EVFSDIV:	ret = AB;	break;
	case EVFSMUL:	ret = AB;	break;
	case EVFSNABS:	ret = XA;	break;
	case EVFSNEG:	ret = XA;	break;
	case EVFSSUB:	ret = AB;	break;

	case EFDABS:	ret = XA;	break;
	case EFDADD:	ret = AB;	break;
	case EFDCFS:	ret = XB;	break;
	case EFDCMPEQ:	ret = XCR;	break;
	case EFDCMPGT:	ret = XCR;	break;
	case EFDCMPLT:	ret = XCR;	break;
	case EFDCTSF:	ret = XB;	break;
	case EFDCTSI:	ret = XB;	break;
	case EFDCTSIDZ:	ret = XB;	break;
	case EFDCTSIZ:	ret = XB;	break;
	case EFDCTUF:	ret = XB;	break;
	case EFDCTUI:	ret = XB;	break;
	case EFDCTUIDZ:	ret = XB;	break;
	case EFDCTUIZ:	ret = XB;	break;
	case EFDDIV:	ret = AB;	break;
	case EFDMUL:	ret = AB;	break;
	case EFDNABS:	ret = XA;	break;
	case EFDNEG:	ret = XA;	break;
	case EFDSUB:	ret = AB;	break;
	}

	return ret;
}