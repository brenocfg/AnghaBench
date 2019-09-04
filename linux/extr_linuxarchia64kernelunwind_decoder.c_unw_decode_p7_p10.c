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
typedef  int /*<<< orphan*/  unw_word ;

/* Variables and functions */
 int /*<<< orphan*/  P10 ; 
 int /*<<< orphan*/  P7 ; 
 int /*<<< orphan*/  P8 ; 
 int /*<<< orphan*/  P9 ; 
 int /*<<< orphan*/  UNW_DEC_ABI (int /*<<< orphan*/ ,unsigned char,unsigned char,void*) ; 
 int /*<<< orphan*/  UNW_DEC_BAD_CODE (unsigned char) ; 
 int /*<<< orphan*/  UNW_DEC_GR_GR (int /*<<< orphan*/ ,unsigned char,unsigned char,void*) ; 
 int /*<<< orphan*/  UNW_DEC_MEM_STACK_F (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  UNW_DEC_MEM_STACK_V (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  UNW_DEC_PRIUNAT_PSPREL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  UNW_DEC_PRIUNAT_SPREL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  UNW_DEC_PRIUNAT_WHEN_GR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  UNW_DEC_PRIUNAT_WHEN_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  UNW_DEC_REG_PSPREL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  UNW_DEC_REG_SPREL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  UNW_DEC_REG_WHEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  UNW_DEC_SPILL_BASE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  UNW_REG_BSP ; 
 int /*<<< orphan*/  UNW_REG_BSPSTORE ; 
 int /*<<< orphan*/  UNW_REG_FPSR ; 
 int /*<<< orphan*/  UNW_REG_LC ; 
 int /*<<< orphan*/  UNW_REG_PFS ; 
 int /*<<< orphan*/  UNW_REG_PR ; 
 int /*<<< orphan*/  UNW_REG_PSP ; 
 int /*<<< orphan*/  UNW_REG_RNAT ; 
 int /*<<< orphan*/  UNW_REG_RP ; 
 int /*<<< orphan*/  UNW_REG_UNAT ; 
 int /*<<< orphan*/  unw_decode_uleb128 (unsigned char**) ; 
 unsigned char* unw_decode_x1 (unsigned char*,unsigned char,void*) ; 
 unsigned char* unw_decode_x2 (unsigned char*,unsigned char,void*) ; 
 unsigned char* unw_decode_x3 (unsigned char*,unsigned char,void*) ; 
 unsigned char* unw_decode_x4 (unsigned char*,unsigned char,void*) ; 

__attribute__((used)) static unsigned char *
unw_decode_p7_p10 (unsigned char *dp, unsigned char code, void *arg)
{
  unsigned char r, byte1, byte2;
  unw_word t, size;

  if ((code & 0x10) == 0)
    {
      r = (code & 0xf);
      t = unw_decode_uleb128 (&dp);
      switch (r)
	{
	case 0:
	  size = unw_decode_uleb128 (&dp);
	  UNW_DEC_MEM_STACK_F(P7, t, size, arg);
	  break;

	case 1: UNW_DEC_MEM_STACK_V(P7, t, arg); break;
	case 2: UNW_DEC_SPILL_BASE(P7, t, arg); break;
	case 3: UNW_DEC_REG_SPREL(P7, UNW_REG_PSP, t, arg); break;
	case 4: UNW_DEC_REG_WHEN(P7, UNW_REG_RP, t, arg); break;
	case 5: UNW_DEC_REG_PSPREL(P7, UNW_REG_RP, t, arg); break;
	case 6: UNW_DEC_REG_WHEN(P7, UNW_REG_PFS, t, arg); break;
	case 7: UNW_DEC_REG_PSPREL(P7, UNW_REG_PFS, t, arg); break;
	case 8: UNW_DEC_REG_WHEN(P7, UNW_REG_PR, t, arg); break;
	case 9: UNW_DEC_REG_PSPREL(P7, UNW_REG_PR, t, arg); break;
	case 10: UNW_DEC_REG_WHEN(P7, UNW_REG_LC, t, arg); break;
	case 11: UNW_DEC_REG_PSPREL(P7, UNW_REG_LC, t, arg); break;
	case 12: UNW_DEC_REG_WHEN(P7, UNW_REG_UNAT, t, arg); break;
	case 13: UNW_DEC_REG_PSPREL(P7, UNW_REG_UNAT, t, arg); break;
	case 14: UNW_DEC_REG_WHEN(P7, UNW_REG_FPSR, t, arg); break;
	case 15: UNW_DEC_REG_PSPREL(P7, UNW_REG_FPSR, t, arg); break;
	default: UNW_DEC_BAD_CODE(r); break;
	}
    }
  else
    {
      switch (code & 0xf)
	{
	case 0x0: /* p8 */
	  {
	    r = *dp++;
	    t = unw_decode_uleb128 (&dp);
	    switch (r)
	      {
	      case  1: UNW_DEC_REG_SPREL(P8, UNW_REG_RP, t, arg); break;
	      case  2: UNW_DEC_REG_SPREL(P8, UNW_REG_PFS, t, arg); break;
	      case  3: UNW_DEC_REG_SPREL(P8, UNW_REG_PR, t, arg); break;
	      case  4: UNW_DEC_REG_SPREL(P8, UNW_REG_LC, t, arg); break;
	      case  5: UNW_DEC_REG_SPREL(P8, UNW_REG_UNAT, t, arg); break;
	      case  6: UNW_DEC_REG_SPREL(P8, UNW_REG_FPSR, t, arg); break;
	      case  7: UNW_DEC_REG_WHEN(P8, UNW_REG_BSP, t, arg); break;
	      case  8: UNW_DEC_REG_PSPREL(P8, UNW_REG_BSP, t, arg); break;
	      case  9: UNW_DEC_REG_SPREL(P8, UNW_REG_BSP, t, arg); break;
	      case 10: UNW_DEC_REG_WHEN(P8, UNW_REG_BSPSTORE, t, arg); break;
	      case 11: UNW_DEC_REG_PSPREL(P8, UNW_REG_BSPSTORE, t, arg); break;
	      case 12: UNW_DEC_REG_SPREL(P8, UNW_REG_BSPSTORE, t, arg); break;
	      case 13: UNW_DEC_REG_WHEN(P8, UNW_REG_RNAT, t, arg); break;
	      case 14: UNW_DEC_REG_PSPREL(P8, UNW_REG_RNAT, t, arg); break;
	      case 15: UNW_DEC_REG_SPREL(P8, UNW_REG_RNAT, t, arg); break;
	      case 16: UNW_DEC_PRIUNAT_WHEN_GR(P8, t, arg); break;
	      case 17: UNW_DEC_PRIUNAT_PSPREL(P8, t, arg); break;
	      case 18: UNW_DEC_PRIUNAT_SPREL(P8, t, arg); break;
	      case 19: UNW_DEC_PRIUNAT_WHEN_MEM(P8, t, arg); break;
	      default: UNW_DEC_BAD_CODE(r); break;
	    }
	  }
	  break;

	case 0x1:
	  byte1 = *dp++; byte2 = *dp++;
	  UNW_DEC_GR_GR(P9, (byte1 & 0xf), (byte2 & 0x7f), arg);
	  break;

	case 0xf: /* p10 */
	  byte1 = *dp++; byte2 = *dp++;
	  UNW_DEC_ABI(P10, byte1, byte2, arg);
	  break;

	case 0x9:
	  return unw_decode_x1 (dp, code, arg);

	case 0xa:
	  return unw_decode_x2 (dp, code, arg);

	case 0xb:
	  return unw_decode_x3 (dp, code, arg);

	case 0xc:
	  return unw_decode_x4 (dp, code, arg);

	default:
	  UNW_DEC_BAD_CODE(code);
	  break;
	}
    }
  return dp;
}